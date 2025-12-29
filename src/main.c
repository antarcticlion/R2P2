/* Raspi SDK */
#include <pico/stdlib.h>
#include <pico/bootrom.h>
#include <bsp/board.h>
#include <tusb.h>
#include <hardware/clocks.h>

#include <stdio.h>
#include <string.h>

#ifdef RP2350_WITH_PSRAM
#ifdef RP2350_PSRAM_CS
#include "rp2_psram.h"
#endif
#endif

/* PicoRuby */
#include "picoruby.h"
#include "picoruby/debug.h"
#include "hal.h" // in picoruby-machine
#include "main_task.c"

#if !defined(HEAP_SIZE)
  #if defined(PICO_RP2040)
    #define RAM_SIZE_KB         264
    #define WIFI_STACK_SIZE_KB   32
  #elif defined(PICO_RP2350)
    #define RAM_SIZE_KB         524
    #define WIFI_STACK_SIZE_KB   80
  #else
    #error "PICO_RP2040 or PICO_RP2350 must be defined"
  #endif
  // Compiling a big Ruby code may need more stack size
  #define BASIC_STACK_SIZE_KB   80
  #if defined(USE_WIFI)
    #define STACK_SIZE_KB (BASIC_STACK_SIZE_KB + WIFI_STACK_SIZE_KB)
  #else
    #define STACK_SIZE_KB BASIC_STACK_SIZE_KB
  #endif
  #define HEAP_SIZE_KB (RAM_SIZE_KB - STACK_SIZE_KB)
  #define HEAP_SIZE (HEAP_SIZE_KB * 1024)
#endif

#if defined(R2P2_ALLOC_LIBC)
  #define heap_pool NULL
#else
  static uint8_t heap_pool_entity[HEAP_SIZE] __attribute__((aligned(8)));
  static uint8_t *heap_pool = heap_pool_entity;
#endif

#if defined(PICORB_VM_MRUBY)
  mrb_state *global_mrb = NULL;
#endif

#ifdef RP2350_WITH_PSRAM
#ifdef RP2350_PSRAM_CS

#define PSRAM_START 0x11000000
int deep_psram_test(size_t psram_size) {
    volatile uint32_t *psram = (uint32_t *)PSRAM_START;
    size_t words = psram_size / sizeof(uint32_t);

    printf("Starting Deep PSRAM Diagnosis...\n");

    // 1. Data Line Test (Walking 1s)
    // Whether each bit of data is independent and does not interfere with adjacent bits
    printf("Test 1: Walking 1s (Data lines)... ");
    for(int i = 0; i < 32; i++) {
        uint32_t pattern = (1 << i);
        psram[0] = pattern;
        if (psram[0] != pattern) {
            printf("Failed at bit %d (Read back: 0x%08X)\n", i, (unsigned int)psram[0]);
            return 1;
        }
    }
    printf("Passed.\n");

    // 2. Address Line Test
    // Address lines are not shorted, and specific bits are not fixed.
    printf("Test 2: Address line integrity... ");
    for (int i = 0; (1 << i) < words; i++) {
        psram[1 << i] = (uint32_t)(1 << i);
    }
    for (int i = 0; (1 << i) < words; i++) {
        if (psram[1 << i] != (uint32_t)(1 << i)) {
            printf("Failed at offset 0x%X\n", (1 << i));
            return 2;
        }
    }
    printf("Passed.\n");

    // 3. Inverse Pattern Full Scan
    // Whether the written value and its inverted value are correctly retained for all areas
    printf("Test 3: Full area pattern scan... ");
    for (size_t i = 0; i < words; i++) {
        psram[i] = (uint32_t)i;
    }
    for (size_t i = 0; i < words; i++) {
        if (psram[i] != (uint32_t)i) {
            printf("Failed at index %zu (Read: 0x%X, Expected: 0x%X)\n", i, (unsigned int)psram[i], (unsigned int)i);
            return 4;
        }
        // Flip and retest
        psram[i] = ~(uint32_t)i;
        if (psram[i] != ~(uint32_t)i) {
            printf("Failed at index %zu (Inverted)\n", i);
            return 5;
        }
    }
    printf("Passed.\n");

    printf("PSRAM Diagnosis: ALL PASSED. Safe to use as Heap.\n");
    return 0;
}

static int psram_test_passed = 0;
#endif
#endif

int
main(void)
{
  stdio_init_all();
  // printf() goes to Picoprobe UART
  printf("R2P2 PicoRuby starting...\n");
  printf("Heap size: %d KB\n", HEAP_SIZE_KB);
  board_init();

  uint32_t heap_size = HEAP_SIZE;

#ifdef RP2350_WITH_PSRAM
#ifdef RP2350_PSRAM_CS
  size_t psram_size = psram_init(RP2350_PSRAM_CS);
  printf("PSRAM SIZE %d\n", psram_size);
  psram_test_passed = deep_psram_test(psram_size);
#endif
#endif

#if defined(PICO_DEFAULT_LED_PIN)
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    sleep_ms(750);
#endif


#ifdef RP2350_WITH_PSRAM
#ifdef RP2350_PSRAM_CS
  if(heap_pool != NULL){
    if(psram_size != 0){
      if(!psram_test_passed){
        heap_pool = (uint8_t *)(PSRAM_START);
        heap_size = psram_size;
      }
    }
  }

#if defined(PICO_DEFAULT_LED_PIN)
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(250);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    sleep_ms(750);

    while(psram_test_passed--){
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(250);
    }
#endif
#endif
#endif

  int ret = 0;

#if defined(PICORB_VM_MRUBY)
  mrb_state *mrb = mrb_open_with_custom_alloc(heap_pool, heap_size);
  global_mrb = mrb;
  mrc_irep *irep = mrb_read_irep(mrb, main_task);
  mrc_ccontext *cc = mrc_ccontext_new(mrb);
  mrb_value name = mrb_str_new_lit(mrb, "R2P2");
  mrb_value task = mrc_create_task(cc, irep, name, mrb_nil_value(), mrb_obj_value(mrb->top_self));
  if (mrb_nil_p(task)) {
    const char *msg = "mrbc_create_task failed\n";
    hal_write(1, msg, strlen(msg));
    ret = 1;
  }
  else {
    mrb_tasks_run(mrb);
  }
  if (mrb->exc) {
    mrb_print_error(mrb);
    ret = 1;
  }
  mrb_close(mrb);
  mrc_ccontext_free(cc);
#elif defined(PICORB_VM_MRUBYC)
  mrbc_init(heap_pool, heap_size);
  mrbc_tcb *main_tcb = mrbc_create_task(main_task, 0);
  if (!main_tcb) {
    const char *msg = "mrbc_create_task failed\n";
    hal_write(1, msg, strlen(msg));
    ret = 1;
  }
  else {
    mrbc_set_task_name(main_tcb, "main_task");
    mrbc_vm *vm = &main_tcb->vm;
    picoruby_init_require(vm);
    mrbc_run();
  }
#endif
  return ret;
}

