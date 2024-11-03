# MF-34

A customizable 34  keyboard, support both HOTSWAP and SOLDER.

* Keyboard Maintainer: [gezhaoyou](https://github.com/gezhaoyou)
* Hardware Supported: [gezhaoyou](https://github.com/gezhaoyou)

Make example for this keyboard (after setting up your build environment):

    make magic_force/mf34:default

Flashing example for this keyboard:

    make magic_force/mf34:default:flash

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button: [boot] first, then press button: [reset]  on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

----
# above is the default readme.md content
---

# DFU
按住esc键，然后插入usb线，然后松开esc键，就进入了dfu模式。

# compile
```shell
qmk compile -kb magic_force/mf34 -km vial_test
```

# VSCODE 
下载安装 clangd 插件
```shell
qmk generate-compilation-database -kb magic_force/mf34 -km vial_test
```
生成 `compile_commands.json`
`clangd: Download Language Server`


# DEBUG 
首先要有` CONSOLE_ENABLE = yes` in your rules.mk.  \
打开 debug mode 可以增加 debug output.   \
一种方式是Use the `DB_TOGG` keycode in keymap, use the `Command` feature to enable debug mode.  \
另一种方式是Add the following code to your keymap.  
```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```
处理RGB灯效的函数，就在`process_rgb.c`文件中。  \
```c
bool process_rgb(const uint16_t keycode, const keyrecord_t *record) {
```
# 运行机制
`main()`函数中的while循环，调用`protocol_keyboard_task();`函数，这个函数就是`keyboard_task();`函数。

`RGB_MATRIX_ENABLE`宏会启动`rgb_matrix_task();`函数。这个函数里或许可以根据`layer_state`的状态来控制灯效的开关。

# 处理模式切换
`QK_MOMENTARY` 从这里出发

這個函数已经带有了layer的信息
```c
action_t action_for_key(uint8_t layer, keypos_t key) {
```

`action_layer.h` 这个文件中定义了`extern layer_state_t layer_state;`  \
可以从这个变量中获取当前的layer状态。  \

# 和light相关的代码
```text
C:\gitroot\vial-qmk\docs\features\rgblight.md
  318,34:             rgblight_blink_layer(debug_enable ? 0 : 1, 500);
  335,41:             rgblight_blink_layer_repeat(debug_enable ? 0 : 1, 200, 3);
```

# 遗留问题
rgb_matrix_task 和 以下代码是如何互动的？
```c
@@ -78,6 +81,7 @@ bool process_rgb(const uint16_t keycode, const keyrecord_t *record) {
 #endif
                 return false;
             case QK_UNDERGLOW_MODE_NEXT:
```

json文件时如何被编辑进固件中的

# 看下RGB toggle是怎么起作用的
quantum_keycodes_legacy.h #define RGB_TOG QK_UNDERGLOW_TOGGLE   \
看起来应该可以用这个函数来开关灯光 rgb_matrix_toggle();   、
试着把这个函数加入到layout中 或者 加到MO/TG 中

好像生效了，以后直接用rgb_matrix_toggle就可以了

# 无语之处 Bugs
QMK toolbox 居然不能清屏，不然会死掉

# 编译的文件
```log
Generating: .build/obj_magic_force_mf34_vial_test/src/info_deps.d                                   [OK]
arm-none-eabi-gcc.exe (GCC) 12.2.0
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Generating: .build/obj_magic_force_mf34_vial_test/src/info_config.h                                 [OK]
Generating: .build/obj_magic_force_mf34_vial_test/src/default_keyboard.c                            [OK]
Generating: .build/obj_magic_force_mf34_vial_test/src/default_keyboard.h                            [OK]
Compiling: keyboards/magic_force/mf34/mf34.c                                                        [OK]
Compiling: .build/obj_magic_force_mf34_vial_test/src/default_keyboard.c                             [OK]
Compiling: quantum/keymap_introspection.c                                                           [OK]
Compiling: quantum/quantum.c                                                                        [OK]
Compiling: quantum/bitwise.c                                                                        [OK]
Compiling: quantum/led.c                                                                            [OK]
Compiling: quantum/action.c                                                                         [OK]
Compiling: quantum/action_layer.c                                                                   [OK]
Compiling: quantum/action_tapping.c                                                                 [OK]
Compiling: quantum/action_util.c                                                                    [OK]
Compiling: quantum/eeconfig.c                                                                       [OK]
Compiling: quantum/keyboard.c                                                                       [OK]
Compiling: quantum/keymap_common.c                                                                  [OK]
Compiling: quantum/keycode_config.c                                                                 [OK]
Compiling: quantum/sync_timer.c                                                                     [OK]
Compiling: quantum/logging/debug.c                                                                  [OK]
Compiling: quantum/logging/sendchar.c                                                               [OK]
Compiling: quantum/logging/print.c                                                                  [OK]
Compiling: quantum/matrix_common.c                                                                  [OK]
Compiling: quantum/matrix.c                                                                         [OK]
Compiling: quantum/debounce/sym_defer_g.c                                                           [OK]
Compiling: quantum/main.c                                                                           [OK]
Compiling: lib/printf/src/printf/printf.c                                                           [OK]
Compiling: drivers/eeprom/eeprom_driver.c                                                           [OK]
Compiling: platforms/chibios/drivers/eeprom/eeprom_legacy_emulated_flash.c                          [OK]
Compiling: platforms/chibios/drivers/flash/legacy_flash_ops.c                                       [OK]
Compiling: quantum/color.c                                                                          [OK]
Compiling: quantum/rgb_matrix/rgb_matrix.c                                                          [OK]
Compiling: quantum/rgb_matrix/rgb_matrix_drivers.c                                                  [OK]
Compiling: quantum/process_keycode/process_rgb.c                                                    [OK]
Compiling: quantum/led_tables.c                                                                     [OK]
Compiling: quantum/vial.c                                                                          quantum/vial.c:30:9: note: '#pragma message: Building Vial-enabled firmware in insecure mode.'
   30 | #pragma message "Building Vial-enabled firmware in insecure mode."
      |         ^~~~~~~
 [OK]
Compiling: quantum/qmk_settings.c                                                                   [OK]
Compiling: lib/lib8tion/lib8tion.c                                                                  [OK]
Compiling: platforms/chibios/drivers/ws2812_bitbang.c                                               [OK]
Compiling: quantum/process_keycode/process_auto_shift.c                                             [OK]
Compiling: quantum/bootmagic/bootmagic.c                                                            [OK]
Compiling: quantum/process_keycode/process_combo.c                                                  [OK]
Compiling: quantum/command.c                                                                        [OK]
Compiling: quantum/dynamic_keymap.c                                                                 [OK]
Compiling: quantum/process_keycode/process_grave_esc.c                                              [OK]
Compiling: quantum/process_keycode/process_key_override.c                                           [OK]
Compiling: quantum/process_keycode/process_magic.c                                                  [OK]
Compiling: quantum/mousekey.c                                                                       [OK]
Compiling: quantum/send_string/send_string.c                                                        [OK]
Compiling: quantum/process_keycode/process_space_cadet.c                                            [OK]
Compiling: quantum/process_keycode/process_tap_dance.c                                              [OK]
Compiling: quantum/process_keycode/process_tri_layer.c                                              [OK]
Compiling: quantum/tri_layer.c                                                                      [OK]
Compiling: quantum/via.c                                                                            [OK]
Compiling: tmk_core/protocol/host.c                                                                 [OK]
Compiling: tmk_core/protocol/report.c                                                               [OK]
Compiling: tmk_core/protocol/usb_device_state.c                                                     [OK]
Compiling: tmk_core/protocol/usb_util.c                                                             [OK]
Compiling: platforms/suspend.c                                                                      [OK]
Compiling: platforms/synchronization_util.c                                                         [OK]
Compiling: platforms/timer.c                                                                        [OK]
Compiling: platforms/chibios/hardware_id.c                                                          [OK]
Compiling: platforms/chibios/platform.c                                                             [OK]
Compiling: platforms/chibios/suspend.c                                                              [OK]
Compiling: platforms/chibios/timer.c                                                                [OK]
Compiling: platforms/chibios/bootloaders/stm32_dfu.c                                                [OK]
Assembling: lib/chibios/os/common/startup/ARMCMx/compilers/GCC/crt0_v6m.S                           [OK]
Assembling: lib/chibios/os/common/startup/ARMCMx/compilers/GCC/vectors.S                            [OK]
Assembling: lib/chibios/os/common/ports/ARMv6-M/compilers/GCC/chcoreasm.S                           [OK]
Compiling: tmk_core/protocol/chibios/usb_main.c                                                     [OK]
Compiling: tmk_core/protocol/chibios/chibios.c                                                      [OK]
Compiling: tmk_core/protocol/usb_descriptor.c                                                       [OK]
Compiling: tmk_core/protocol/chibios/usb_driver.c                                                   [OK]
Compiling: tmk_core/protocol/chibios/usb_endpoints.c                                                [OK]
Compiling: tmk_core/protocol/chibios/usb_report_handling.c                                          [OK]
Compiling: tmk_core/protocol/chibios/usb_util.c                                                     [OK]
Compiling: lib/chibios/os/common/startup/ARMCMx/compilers/GCC/crt1.c                                [OK]
Compiling: lib/chibios/os/rt/src/chsys.c                                                            [OK]
Compiling: lib/chibios/os/rt/src/chrfcu.c                                                           [OK]
Compiling: lib/chibios/os/rt/src/chdebug.c                                                          [OK]
Compiling: lib/chibios/os/rt/src/chtrace.c                                                          [OK]
Compiling: lib/chibios/os/rt/src/chvt.c                                                             [OK]
Compiling: lib/chibios/os/rt/src/chschd.c                                                           [OK]
Compiling: lib/chibios/os/rt/src/chinstances.c                                                      [OK]
Compiling: lib/chibios/os/rt/src/chthreads.c                                                        [OK]
Compiling: lib/chibios/os/rt/src/chtm.c                                                             [OK]
Compiling: lib/chibios/os/rt/src/chstats.c                                                          [OK]
Compiling: lib/chibios/os/rt/src/chregistry.c                                                       [OK]
Compiling: lib/chibios/os/rt/src/chsem.c                                                            [OK]
Compiling: lib/chibios/os/rt/src/chmtx.c                                                            [OK]
Compiling: lib/chibios/os/rt/src/chcond.c                                                           [OK]
Compiling: lib/chibios/os/rt/src/chevents.c                                                         [OK]
Compiling: lib/chibios/os/rt/src/chmsg.c                                                            [OK]
Compiling: lib/chibios/os/rt/src/chdynamic.c                                                        [OK]
Compiling: lib/chibios/os/common/ports/ARMv6-M/chcore.c                                             [OK]
Compiling: lib/chibios/os/hal/osal/rt-nil/osal.c                                                    [OK]
Compiling: lib/chibios/os/oslib/src/chmboxes.c                                                      [OK]
Compiling: lib/chibios/os/oslib/src/chmemcore.c                                                     [OK]
Compiling: lib/chibios/os/oslib/src/chmemheaps.c                                                    [OK]
Compiling: lib/chibios/os/oslib/src/chmempools.c                                                    [OK]
Compiling: lib/chibios/os/oslib/src/chpipes.c                                                       [OK]
Compiling: lib/chibios/os/oslib/src/chobjcaches.c                                                   [OK]
Compiling: lib/chibios/os/oslib/src/chdelegates.c                                                   [OK]
Compiling: lib/chibios/os/oslib/src/chfactory.c                                                     [OK]
Compiling: lib/chibios/os/hal/src/hal.c                                                             [OK]
Compiling: lib/chibios/os/hal/src/hal_st.c                                                          [OK]
Compiling: lib/chibios/os/hal/src/hal_buffers.c                                                     [OK]
Compiling: lib/chibios/os/hal/src/hal_queues.c                                                      [OK]
Compiling: lib/chibios/os/hal/src/hal_flash.c                                                       [OK]
Compiling: lib/chibios/os/hal/src/hal_mmcsd.c                                                       [OK]
Compiling: lib/chibios/os/hal/src/hal_adc.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_can.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_crypto.c                                                      [OK]
Compiling: lib/chibios/os/hal/src/hal_dac.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_efl.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_gpt.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_i2c.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_i2s.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_icu.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_mac.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_mmc_spi.c                                                     [OK]
Compiling: lib/chibios/os/hal/src/hal_pal.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_pwm.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_rtc.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_sdc.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_serial.c                                                      [OK]
Compiling: lib/chibios/os/hal/src/hal_serial_usb.c                                                  [OK]
Compiling: lib/chibios/os/hal/src/hal_sio.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_spi.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_trng.c                                                        [OK]
Compiling: lib/chibios/os/hal/src/hal_uart.c                                                        [OK]
Compiling: lib/chibios/os/hal/src/hal_usb.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_wdg.c                                                         [OK]
Compiling: lib/chibios/os/hal/src/hal_wspi.c                                                        [OK]
Compiling: lib/chibios/os/hal/ports/common/ARMCMx/nvic.c                                            [OK]
Compiling: lib/chibios/os/hal/ports/STM32/STM32F0xx/stm32_isr.c                                     [OK]
Compiling: lib/chibios/os/hal/ports/STM32/STM32F0xx/hal_lld.c                                       [OK]
Compiling: lib/chibios/os/hal/ports/STM32/STM32F0xx/hal_efl_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/ADCv1/hal_adc_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/CANv1/hal_can_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/DACv1/hal_dac_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/DMAv1/stm32_dma.c                                     [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/EXTIv1/stm32_exti.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/GPIOv2/hal_pal_lld.c                                  [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/I2Cv2/hal_i2c_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/RTCv2/hal_rtc_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/SPIv2/hal_i2s_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/SPIv2/hal_spi_v2_lld.c                                [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/SYSTICKv1/hal_st_lld.c                                [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/TIMv1/hal_gpt_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/TIMv1/hal_icu_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/TIMv1/hal_pwm_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/USARTv2/hal_serial_lld.c                              [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/USARTv2/hal_sio_lld.c                                 [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/USARTv2/hal_uart_lld.c                                [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/USBv1/hal_usb_lld.c                                   [OK]
Compiling: lib/chibios/os/hal/ports/STM32/LLD/xWDGv1/hal_wdg_lld.c                                  [OK]
Compiling: lib/chibios/os/hal/boards/ST_NUCLEO64_F072RB/board.c                                     [OK]
Compiling: lib/chibios/os/hal/lib/streams/chprintf.c                                                [OK]
Compiling: lib/chibios/os/hal/lib/streams/chscanf.c                                                 [OK]
Compiling: lib/chibios/os/hal/lib/streams/memstreams.c                                              [OK]
Compiling: lib/chibios/os/hal/lib/streams/nullstreams.c                                             [OK]
Compiling: lib/chibios/os/hal/lib/streams/bufstreams.c                                              [OK]
Compiling: lib/chibios/os/various/syscalls.c                                                        [OK]
Compiling: platforms/chibios/syscall-fallbacks.c                                                    [OK]
Compiling: platforms/chibios/wait.c                                                                 [OK]
Compiling: platforms/chibios/synchronization_util.c                                                 [OK]
Compiling: platforms/chibios/interrupt_handlers.c                                                   [OK]
Linking: .build/magic_force_mf34_vial_test.elf                                                      [OK]
Creating binary load file for flashing: .build/magic_force_mf34_vial_test.bin                       [OK]
Creating load file for flashing: .build/magic_force_mf34_vial_test.hex                              [OK]
```