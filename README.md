# Простая эмуляция работы слот машины
### Правила начисления очков
Три одинаковых символа на одной линии:<br />
7 – 100 очков<br />
Арбуз – 80 очков<br />
Лимон – 60 очков<br />
Вишня – 40 очков<br />
Слива – 20 очков<br />
Два одинаковых символа и один другой символ на линии: Начисляется 10% от основного выигрыша символа.<br />
Несовпадающие символы на линии: 0 очков.<br />
Итоговый счёт — это сумма очков всех выигрышных линий.

# Инструкция по сборке

### Требования:
- Visual Studio 2019 (или выше)
- SFML 2.6.2-windows-vc16-64-bit

### Шаги для сборки:
1. Открыть SlotMachine.sln в Visual Studio.
2. Выберите конфигурацию "Release" и платформу "x64".
3. В свойствах проекта указать пути до .include и .lib файлов SFML 
5. Cкопируйте все .dll файлы без префикса d из папки SFML-2.6.2\bin в папку Release где находится .exe файл
6. Соберите и запустите проект
