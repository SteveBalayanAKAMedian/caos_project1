# Постановка
Написать "модуль" компилятора, реализующий операции целочисленного div и mod для константного делителя без использования соответствующих инструкций процессора.
Для процессора делить $-$ довольно ресурсоемкая операция, поэтому компиляторы умеют оптимизировать такие штуки в набор инструкций сдвига и битовых операций.

# Решение
## Общая идея
Вспомним, что деление $-$ это обратная операция к умножению. То есть деление на константу $-$ это умножение на обратный к ней элемент. Но встаёт вопрос: а в каком кольце (по какому модулю)? Как считать это обратное? И как быть с отрицательными числами? Для ответов на эти вопросы сначала посмотрим, как числа делятся в языке С. Рассмотрим 4 примера:
1.  13 / 5 = 2; mod = 3

2. -13 / 5 = -2; mod = -3

3. 13 / -5 = -2; mod = 3

4. -13 / -5 = 2; mod = -3

Получается, нам достаточно научиться делить в случае натуральных чисел. Для деления целых приведём их по модулю к натуральным (целым беззнаковым). Обозначим делимое как $n$, делитель как $d$, частное как $q$, остаток как $mod$, получим следующие уравнения: \
$\frac{|n|}{|d|} = |q|$ \
$sgn(q) = sgn(n) \cdot sgn(d)$ \
$mod = n - d \cdot q$ 

## Вычисление обратного
Остаётся самый нетривиальный момент $-$ как точно и эффективно считать обратный элемент для константы $d$. Первой идеей решения было воспользоваться расширенным алгоритмом Евклида и радостно считать обратный по модулю. Но он же корректно определён для простого модуля, такое решение не очень масштабируемо. Гугление привело меня к [оригинальной статье](https://gmplib.org/~tege/divcnst-pldi94.pdf), в которой описан и доказан алгоритм приближения $\frac{1}{d}$ как $\frac{x}{y}$, где $y$ $-$ степень двойки. 

Пусть мы хотим посчитать $q = \lfloor n / d \rfloor$, где $0 < d < 2^N$ константа и $0 \leq n < 2^N$ переменная. Найдём приближение $m / 2^{N + l}$ для $1 / d$ такое, что $\lfloor \frac{n}{d} \rfloor = \lfloor \frac{m \cdot n}{2^{N + l}} \rfloor$, $0 < n \leq 2^{N} - 1$. В статье доказывается, что такое приближение существует, верно неравенство $2^{N + l} \leq m \cdot d \leq 2^{N + l} + 2^l$ и что можно вместо честного умножения на $m$ умножить на $2^N$ и на $m - 2^N$. Поэтому в предподсчёте используется $m' = \lfloor 2^{N} \cdot (2^l - d) /d \rfloor + 1 $, где $l = \lceil\log_2 d\rceil $.

Таким образом деление используется только на моменте предподсчёта. 

# Запуск
В корне проекта:
```
make -f  make/defaultMakefile && ./default_div
```

# Дополнительные замечания
В [данной статье](https://arxiv.org/pdf/1902.01961.pdf) рассматривается более быстрый алгоритм получения модуля числа. А в [данной статье](https://arxiv.org/pdf/2012.12369.pdf) рассматривается более быстрое деление. В дальнейшем будет проведено сравнение скоростей этих алгоритмов. 
