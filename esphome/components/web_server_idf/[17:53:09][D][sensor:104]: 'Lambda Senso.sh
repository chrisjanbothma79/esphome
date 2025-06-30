[17:53:09][D][sensor:104]: 'Lambda Sensor 15': Sending state 15.00000  with 1 decimals of accuracy
[17:53:09][D][sensor:104]: 'Lambda Sensor 34': Sending state 34.00000  with 1 decimals of accuracy
[17:53:10][D][sensor:104]: 'Lambda Sensor 16': Sending state 16.00000  with 1 decimals of accuracy
[17:53:10][D][sensor:104]: 'Lambda Sensor 7': Sending state 7.00000  with 1 decimals of accuracy
[17:53:12][D][esp-idf:000]: W (92465) httpd_txrx: httpd_sock_err: error in send : 9
[17:53:12]Guru Meditation Error: Core  0 panic'ed (LoadProhibited). Exception was unhandled.

[17:53:12]Core  0 register dump:
[17:53:12]PC      : 0x401a369f  PS      : 0x00060530  A0      : 0x801705f8  A1      : 0x3ffcc9d0  
WARNING Decoded 0x401a369f: std::local_Rb_tree_increment(std::_Rb_tree_node_base*) at /Users/brnomac003/.gitlab-runner/builds/qR2TxTby/0/idf/crosstool-NG/.build/xtensa-esp-elf/src/gcc/libstdc++-v3/src/c++98/tree.cc:65
[17:53:12]A2      : 0x02000241  A3      : 0x3ffcc9c8  A4      : 0x00000008  A5      : 0x3ffe8b84  
[17:53:12]A6      : 0x30303030  A7      : 0x63383030  A8      : 0x3ffe8778  A9      : 0x02000241  
[17:53:12]A10     : 0xfffffffe  A11     : 0x0000003b  A12     : 0x3ffe8b7c  A13     : 0x00000098  
[17:53:12]A14     : 0x00000000  A15     : 0x3ffe36c4  SAR     : 0x00000017  EXCCAUSE: 0x0000001c  
[17:53:12]EXCVADDR: 0x02000249  LBEG    : 0x40082b85  LEND    : 0x40082b8d  LCOUNT  : 0x00000027  


[17:53:12]Backtrace: 0x401a369c:0x3ffcc9d0 0x401705f5:0x3ffcc9f0 0x4010062e:0x3ffcca10 0x400f793a:0x3ffcca30 0x400f08c1:0x3ffcca50 0x400f094d:0x3ffcca80 0x401a03ad:0x3ffccac0 0x401a0461:0x3ffccae0 0x40101566:0x3ffccb00 0x4010586a:0x3ffccb30 0x400e6f76:0x3ffccb50
WARNING Found stack trace! Trying to decode it
WARNING Decoded 0x401a369c: std::local_Rb_tree_increment(std::_Rb_tree_node_base*) at /Users/brnomac003/.gitlab-runner/builds/qR2TxTby/0/idf/crosstool-NG/.build/xtensa-esp-elf/src/gcc/libstdc++-v3/src/c++98/tree.cc:62
WARNING Decoded 0x401705f5: std::_Rb_tree_increment(std::_Rb_tree_node_base const*) at /Users/brnomac003/.gitlab-runner/builds/qR2TxTby/0/idf/crosstool-NG/.build/xtensa-esp-elf/src/gcc/libstdc++-v3/src/c++98/tree.cc:89
WARNING Decoded 0x4010062e: std::_Rb_tree_const_iterator<esphome::web_server_idf::AsyncEventSourceResponse*>::operator++() at /Users/bdraco/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf/include/c++/13.2.0/bits/stl_tree.h:368
 (inlined by) esphome::web_server_idf::AsyncEventSource::try_send_nodefer(char const*, char const*, unsigned long, unsigned long) at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/components/web_server_idf/web_server_idf.cpp:516
WARNING Decoded 0x400f793a: std::_Function_handler<void (unsigned char, char const*, char const*), esphome::web_server::WebServer::setup()::{lambda(int, char const*, char const*)#1}>::_M_invoke(std::_Any_data const&, unsigned char&&, char const*&&, char const*&&) at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/components/web_server/web_server.cpp:247 (discriminator 1)
 (inlined by) __invoke_impl<void, esphome::web_server::WebServer::setup()::<lambda(int, char const*, char const*)>&, unsigned char, char const*, char const*> at /Users/bdraco/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf/include/c++/13.2.0/bits/invoke.h:61 (discriminator 1)
 (inlined by) __invoke_r<void, esphome::web_server::WebServer::setup()::<lambda(int, char const*, char const*)>&, unsigned char, char const*, char const*> at /Users/bdraco/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf/include/c++/13.2.0/bits/invoke.h:111 (discriminator 1)
 (inlined by) _M_invoke at /Users/bdraco/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf/include/c++/13.2.0/bits/std_function.h:290 (discriminator 1)
WARNING Decoded 0x400f08c1: std::function<void (unsigned char, char const*, char const*)>::operator()(unsigned char, char const*, char const*) const at /Users/bdraco/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf/include/c++/13.2.0/bits/std_function.h:591
 (inlined by) esphome::CallbackManager<void (unsigned char, char const*, char const*)>::call(unsigned char, char const*, char const*) at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/core/helpers.h:431
WARNING Decoded 0x400f094d: esphome::logger::Logger::loop() at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/components/logger/logger.cpp:188
 (inlined by) esphome::logger::Logger::loop() at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/components/logger/logger.cpp:155
WARNING Decoded 0x401a03ad: esphome::Component::call_loop() at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/core/component.cpp:84
WARNING Decoded 0x401a0461: esphome::Component::call() at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/core/component.cpp:112
WARNING Decoded 0x40101566: esphome::Application::loop() at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/core/application.cpp:128
WARNING Decoded 0x4010586a: loop() at /Users/bdraco/esphome/.esphome/build/ol/ol.yaml:1345
WARNING Decoded 0x400e6f76: esphome::loop_task(void*) at /Users/bdraco/esphome/.esphome/build/ol/src/esphome/components/esp32/core.cpp:86 (discriminator 1)




[17:53:14]ELF file SHA256: 009865893

[17:53:14]Rebooting...
[17:53:14]ets Jul 29 2019 12:21:46

[17:53:14]rst:0xc (SW_CPU_RESET),boot:0x1b (SPI_FAST_FLASH_BOOT)
[17:53:14]configsip: 0, SPIWP:0xee
[17:53:14]clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
[17:53:14]mode:DIO, clock div:2
[17:53:14]load:0x3fff0030,len:6072
[17:53:14]load:0x40078000,len:14960
[17:53:14]load:0x40080400,len:4
