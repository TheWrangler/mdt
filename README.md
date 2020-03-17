# mdt
使用STM32CubeMX生成STM32F4xx工程

+ 在生成的main()中，应在SystemClock_Config()之后手动添加SystemCoreClockUpdate()函数调用，否则UART、CAN等通信接口的波特率会不正确。
