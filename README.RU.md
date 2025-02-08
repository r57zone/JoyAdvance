[![EN](https://user-images.githubusercontent.com/9499881/33184537-7be87e86-d096-11e7-89bb-f3286f752bc6.png)](https://github.com/r57zone/JoyAdvance/) 
[![RU](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/r57zone/JoyAdvance/blob/master/README.RU.md)

# JoyAdvance
Эмуляция геймпада Xbox для контроллеров DInput. Подключите любой DInput-контроллер - руль, ретро или современный геймпад, назначьте любые кнопки и оси на Xbox-геймпаде, и наслаждайтесь игрой. Работает на базе драйвера [ViGEm](https://github.com/nefarius/ViGEmBus).

## Настройка
1. Установите [ViGEmBus](https://github.com/nefarius/ViGEmBus/releases).
2. Установите Microsoft Visual C++ Redistributable 2017 или новее.
3. Подключите любой DInput-контроллер (руль, ретро или или современный геймпад), кроме Xbox-контроллеров.
4. Распакуйте и запустить JoyAdvance.
5. При необходимости измените профиль по умолчанию, в конфигурационном файле `Config.ini`.
6. Скопируйте профиль по умолчанию `Default.ini`, в папке `Profiles`, и создайте свой профиль. Оси и номера кнопок можно посмотреть в программе для Windows `Joy.cpl`, для её запуска нажмите `Win + R` и введите `joy.cpl`. Названия осей для профиля можно посмотреть в файлах профилей. Проверить результат можно в программе `XInputTest.exe`.
6. При использовании Sony контроллеров со Steam играми, в настройках контроллера, отключите "персональные настройки Playstation".
7. При использовании Sony контроллеров с современными играми, рекомендуется установить [HidHide](https://github.com/nefarius/HidHide/releases), после чего в "HidHide Configuration Client" нужно добавить `JoyAdvance.exe` и включить параметр `Enable device hiding` (если выключен). Необходимо для того, чтобы игра не видела наш контроллер, а видела только эмулируемый Xbox 360 геймпад.

## Загрузка
>Версия для Windows 10, 11.

**[Загрузить](https://github.com/r57zone/JoyAdvance/releases)**

## Благодарности
* [ViGEm](https://github.com/ViGEm) за возможность эмуляции разных геймпадов.

## Сборка
1. Загрузите исходники и распакуйте.
2. [Загрузите Microsoft Visual Studio Code 2017+](https://code.visualstudio.com/download) и [установите](https://github.com/r57zone/RE4ExtendedControl/assets/9499881/69dafce6-fd57-4768-83eb-c1bb69901f07).
3. Измените в свойствах проекта набор инструментов и SDK на ваш.
4. Выберите тип сборки `Release` (если установлен `Debug`) и `x86`, после чего скомплириуйте проект.

## Обратная связь
`r57zone[собака]gmail.com`