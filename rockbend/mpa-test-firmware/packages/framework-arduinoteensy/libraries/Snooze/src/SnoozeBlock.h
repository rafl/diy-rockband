/******************************************************************************
 * Low Power Library
 * Copyright (c) 2019, Colin Duffy https://github.com/duff2013
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *******************************************************************************
 *  Snooze.cpp
 *  Supported Chips:
 *         1. Teensy LC/3.2/3.5/3.6/4.0
 *
 * Purpose:    Provides routines for configuring low power modes.
 *
 * NOTE:       None
 *******************************************************************************/
#ifndef SnoozeBlock_h
#define SnoozeBlock_h

#include "Arduino.h"
//#include "utility/clocks.h"
//#include "utility/sleep.h"
//#include "utility/wake.h"

/**********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
    extern void hal_initialize( void ( * ptr )( void ) );
#ifdef __cplusplus
}
#endif

/***********************************************************************************
 *  REDUCED_CPU_BLOCK - Configures the Teensy to run at 2MHz inside this block
 *
 *  @param SNOOZE_BLOCK - Connected drivers
 *
 *  @return none
 **********************************************************************************/
#define SNOOZE_BLOCK SnoozeBlock &configuration
/*#define TYPE uint8_t
#define REDUCED_CPU_BLOCK( SNOOZE_BLOCK )   \
for ( TYPE __ToDo = SNOOZE_BLOCK.set_runlp( SNOOZE_BLOCK );  __ToDo;  __ToDo = SNOOZE_BLOCK.set_run( SNOOZE_BLOCK ) )*/

/**********************************************************************************/
/*typedef enum {
    TSI          = 3,
    CMP          = 4,
} PIN_TYPE;*/

/***********************************************************************************
 *  Deep Sleep Modes
***********************************************************************************/
/*typedef enum {
    RUN,
    RUN_LP,
    WAIT,
    VLPW,
    STOP,
    VLPS,
    LLS,
    VLLS3,
    VLLS2,
    VLLS1,
    VLLS0
} SLEEP_MODE;*/

/***********************************************************************************
 *  Class SnoozeBlock - Connects low power drivers to Snooze.
 **********************************************************************************/
class SnoozeBlock {
private:
    SnoozeBlock *next_block[8];
    static uint8_t global_block_count;
    int8_t local_block;
    /*******************************************************************************
     *  Driver list to be called after sleep
     *
     *  @param p   Call SnoozeBlock virtual functions
     *  @param idx Array index of the SnoozeBlock list
     ******************************************************************************/
    void reverseList( SnoozeBlock *p, uint8_t idx, uint8_t type ) {
        if ( p != NULL ) {
            reverseList(p->next_block[idx], idx, type );
            if ( p->isUsed ) {
                p->disableDriver( type );
            }
        }
    }
    
    /*******************************************************************************
     *  Driver list to be called before sleep
     *
     *  @param p   Call SnoozeBlock virtual functions
     *  @param idx Array index of the SnoozeBlock
     ******************************************************************************/
    void forwardList( SnoozeBlock *p, uint8_t idx, uint8_t type ) {
        for ( ; p; p = p->next_block[idx] ) {
            if ( p->isUsed ) {
                p->enableDriver( type );
            }
        }
    }
protected:
    /*******************************************************************************
     *  Fired after waking from LLS-VLLS sleep modes
     ******************************************************************************/
    /*static void wakeupIsr( void ) {
        SnoozeBlock *p = SnoozeBlock::root_block[current_block];
        
        if ( mode == VLPW || mode == VLPS ) {
            uint32_t ipsr;
            __asm__ volatile("mrs %0, ipsr\n" : "=r" (ipsr)::);
            switch (ipsr-16) {
                case IRQ_CMP0:
                    p->source = COMPARE_WAKE;
                    break;
#if defined(KINETISK)
                case IRQ_CMP1:
                    p->source = COMPARE_WAKE;
                    break;
                case IRQ_CMP2:
                    p->source = COMPARE_WAKE;
                    break;
#endif
                case IRQ_RTC_ALARM:
                    p->source = ALARM_WAKE;
                    break;
                case IRQ_LPTMR:
                    p->source = TIMER_WAKE;
                    break;
#if !defined(__MK64FX512__)
                case IRQ_TSI:
                    p->source = TOUCH_WAKE;
                    break;
#endif
                default:
                    break;
            }
            
        } else {
            llwuMask.llwuFlag = llwu_clear_flags( );
            pbe_pee( );
        }
        
        for ( ; p; p = p->next_block[current_block] ) p->clearIsrFlags( );
    }*/
    
    static SnoozeBlock *root_block[8];
    static SnoozeBlock *root_class_address[8];
    static uint8_t current_block;
public:
    /*******************************************************************************
     *  Constructor - Recursively connects drivers to this SnoozeBlock using a linked list
     *
     *  @param head Driver
     *  @param tail Driver
     *
     *  @return nothing
     ******************************************************************************/
    template<class ...Tail>
    SnoozeBlock ( SnoozeBlock &head, Tail&... tail ) :  next_block { nullptr, },
                                                        local_block( -1 ),
                                                        isUsed( false ),
                                                        isDriver( false )
    {
        
        // number of drivers left to connected to the Snooze Block
        int i = sizeof...( tail );
        // check for duplicate Drivers
        SnoozeBlock *p = SnoozeBlock::root_block[global_block_count];
        for ( ; p; p = p->next_block[global_block_count] ) {
            if ( p == &head ) {
                // last driver that is a duplicate, increment global block count
                if ( i <= 0 ) {
                    global_block_count++;
                    return;
                }
                // get next driver
                SnoozeBlock( tail... );
                return;
            }
        }
        // update linked list
        // set the root block
        if ( root_block[global_block_count] == NULL ) {
            // On first driver installed call HAL initialization.
            root_class_address[global_block_count] = this;
            root_block[global_block_count] = &head;
            if ( global_block_count == 0 ) {
                // Pass clear_flags function to HAL
                hal_initialize( clear_flags );
            }
        } else {
            p = root_block[global_block_count];
            for ( ; p->next_block[global_block_count]; p = p->next_block[global_block_count] );
            p->next_block[global_block_count] = &head;
        }
        
        next_block[global_block_count] = NULL;
        local_block = global_block_count;
        
        if ( i <= 0 ) {
            global_block_count++;
            return;
        }
        // get next driver
        SnoozeBlock( tail... );
    }
    
    /*******************************************************************************
     *  Constructor - Inherited Drivers call this constructor
     *
     *  @return this
     ******************************************************************************/
    SnoozeBlock ( void ) :
                next_block { nullptr, },
                local_block( -1 ),
                isUsed( false ),
                isDriver( false )
    {

    }
    
    /*******************************************************************************
     *  Deconstructor - Deallocate "this" SnoozeBlock
     ******************************************************************************/
    ~SnoozeBlock ( void ) {
        if ( local_block == -1 ) return;
        if ( root_class_address[local_block] == this ) {
            SnoozeBlock *u;
            SnoozeBlock *p = SnoozeBlock::root_block[local_block];
            u = p;
            while ( p != NULL ) {
                p = p->next_block[local_block];
                u->next_block[local_block] = NULL;
                u = p;
            }
            root_block[local_block] = NULL;
            root_class_address[local_block] = NULL;
            global_block_count--;
        }
    }
    
    /*******************************************************************************
     *  Combine SnoozeBlock(s)
     *
     *  @param replace lhs driver(s) with rhs driver(s)
     *
     *  @return this
     ******************************************************************************/
    SnoozeBlock & operator = ( const SnoozeBlock &rhs ) {
        if ( isDriver ) return *this;
        
        if ( local_block == -1 ) local_block = global_block_count++;
        
        SnoozeBlock *u;
        SnoozeBlock *p = SnoozeBlock::root_block[local_block];
        u = p;
        while ( p != NULL ) {
            p = p->next_block[local_block];
            u->next_block[local_block] = NULL;
            u = p;
        }
        
        if ( rhs.isDriver ) {
            p = ( SnoozeBlock * )&rhs;
            root_block[local_block] = p;
        } else {
            root_block[local_block] = root_block[rhs.local_block];
            p = SnoozeBlock::root_block[rhs.local_block];
            u = SnoozeBlock::root_block[local_block];
            for ( ; p; p = p->next_block[rhs.local_block] ) {
                u->next_block[local_block] = p->next_block[rhs.local_block];
                u = u->next_block[local_block];
            }
        }
        
        next_block[local_block] = NULL;
        
        return *this;
    }

    /*******************************************************************************
     *  Remove SnoozeBlock(s)
     *
     *  @param subtract lhs driver(s) from rhs driver(s)
     *
     *  @return this
     ******************************************************************************/
    SnoozeBlock & operator -= ( const SnoozeBlock &rhs ) {
        if ( isDriver || local_block == -1 ) return *this;
        
        if ( rhs.isDriver ) {
            uint8_t index = 0;
            SnoozeBlock *p = SnoozeBlock::root_block[local_block];
            SnoozeBlock *u = SnoozeBlock::root_block[local_block];
            for ( ; p; p = p->next_block[local_block] ) {
                if ( p == ( SnoozeBlock * )&rhs ) {
                    if ( index == 0 ) {
                        SnoozeBlock::root_block[local_block] = p->next_block[local_block];
                        break;
                    }
                    p = p->next_block[local_block];
                    u->next_block[local_block] = p;
                    break;
                }
                u = p;
                index++;
            }
            return *this;
        }
        
        SnoozeBlock *rhsBlock = SnoozeBlock::root_block[rhs.local_block];
        for ( ; rhsBlock; rhsBlock = rhsBlock->next_block[rhs.local_block] ) {
            uint8_t index = 0;
            SnoozeBlock *p = SnoozeBlock::root_block[local_block];
            SnoozeBlock *u = SnoozeBlock::root_block[local_block];
            for ( ; p; p = p->next_block[local_block] ) {
                if ( p == rhsBlock  ) {
                    if ( index == 0 ) {
                        SnoozeBlock::root_block[local_block] = p->next_block[local_block];
                        break;
                    }
                    p = p->next_block[local_block];
                    u->next_block[local_block] = p;
                    break;
                }
                u = p;
                index++;
            }
        }
        return *this;
    }
    
    /*******************************************************************************
     *  Add SnoozeBlock(s)
     *
     *  @param add lhs driver(s) to rhs driver(s)
     *
     *  @return this
     ******************************************************************************/
    SnoozeBlock & operator += ( const SnoozeBlock &rhs ) {
        if ( isDriver ) return *this;
        if ( local_block == -1 ) local_block = global_block_count++;
        
        if ( rhs.isDriver ) {
            SnoozeBlock *p = SnoozeBlock::root_block[local_block];
            
            for ( ; p; p = p->next_block[local_block] ) if ( p == ( SnoozeBlock * )&rhs ) return *this;
            
            uint8_t idx = local_block;
            p = SnoozeBlock::root_block[idx];
            for ( ; p->next_block[idx]; p = p->next_block[idx] );
            p->next_block[idx] = ( SnoozeBlock * )&rhs;
            next_block[idx] = NULL;
            return *this;
        }
        
        SnoozeBlock *rhsBlock = SnoozeBlock::root_block[rhs.local_block];
        for ( ; rhsBlock; rhsBlock = rhsBlock->next_block[rhs.local_block] ) {
            uint8_t idx = local_block;
            bool flag = false;
            
            if ( root_block[idx] == NULL ) {
                root_block[idx] = rhsBlock;
            } else {
                SnoozeBlock *p;
                for ( p = root_block[idx]; p->next_block[idx]; p = p->next_block[idx] );
                SnoozeBlock *tmpBlock = SnoozeBlock::root_block[idx];
                for ( ; tmpBlock; tmpBlock = tmpBlock->next_block[idx] ) {
                    if ( tmpBlock == rhsBlock ) {
                        flag = true;
                        break;
                    }
                }
                if ( !flag ) p->next_block[idx] = rhsBlock;
            }
            if ( !flag ) next_block[idx] = NULL;
        }
        return *this;
    }

    /*******************************************************************************
     *  Default add SnoozeBlock(s) - does nothing
     *
     *  @param
     *
     *  @return this
     ******************************************************************************/
    SnoozeBlock & operator + ( const SnoozeBlock &rhs ) {
        return *this;
    }

    /*******************************************************************************
     *  Default subtract SnoozeBlock(s) - does nothing
     *
     *  @param
     *
     *  @return this
     ******************************************************************************/
    SnoozeBlock & operator - ( const SnoozeBlock &rhs ) {
        return *this;
    }

    /*******************************************************************************
     *  call drivers enable functions
     ******************************************************************************/
    virtual void enableDriver ( uint8_t type ) {
        if ( local_block == -1 ) return;
        current_block = local_block;
        SnoozeBlock *p = SnoozeBlock::root_block[local_block];
        forwardList( p, local_block, type );
    }
    
    /*******************************************************************************
     *  call drivers disable functions
     ******************************************************************************/
    virtual void disableDriver ( uint8_t type ) {
        if ( local_block == -1 ) return;
        SnoozeBlock *p = SnoozeBlock::root_block[local_block];
        reverseList( p, local_block, type );
    }
    
    /*******************************************************************************
     *  drivers override this function to clear isr flags, gets called in wakeup isr
     ******************************************************************************/
    virtual void clearIsrFlags ( void ) {
    
    }
    
    /*******************************************************************************
     *  called from device's HAL
     ******************************************************************************/
    static void clear_flags( void ) {
        SnoozeBlock *p = SnoozeBlock::root_block[current_block];
        for ( ; p; p = p->next_block[current_block] ) p->clearIsrFlags( );
    }
    
    /*******************************************************************************
     *  called before low speed operation (2 MHZ)
     *
     *  @param SNOOZE_BLOCK
     *
     *  @return true
     ******************************************************************************/
    //uint8_t set_runlp( SNOOZE_BLOCK ) __attribute__((always_inline, unused)) {
        /*SnoozeBlock *p = &configuration;
        p->mode = RUN_LP;
        p->enableDriver( );
        if ( F_CPU == TWO_MHZ ) return 1;
        start_lptmr_systick( );
        pee_blpi( );
        stop_lptmr_systick( 1999 );
        enter_vlpr( );*/
        //return 1;
    //}
    
    /*******************************************************************************
     *  called before high speed operation (F_CPU MHZ)
     *
     *  @param SNOOZE_BLOCK
     *
     *  @return false
     ******************************************************************************/
    //uint8_t set_run( SNOOZE_BLOCK ) __attribute__((always_inline, unused)) {
        /*SnoozeBlock *p = &configuration;
        p->mode = RUN;
        if ( F_CPU == TWO_MHZ ) return 0;
        exit_vlpr( );
        start_lptmr_systick( );
        blpi_pee( );
        stop_lptmr_systick( ( F_CPU / 1000 ) - 1 );
        p->disableDriver( );*/
        //return 0;/
    //}
    
    //DMAMEM static SLEEP_MODE mode;
    //DMAMEM static int source;
    static uint8_t sleepType;
    volatile bool isUsed;
    bool isDriver;
};
#endif /* defined(SnoozeBlock_h) */
