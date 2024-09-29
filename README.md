# Decimal

## Реализация функций библиотеки decimal.h

- Библиотека разработана на языке С стандарта C11 с использованием компиятора gcc;
- Код библиотеки находится в папке src в ветке develop;
- Выдержан Google Style;
- Решение оформлено как статическая библиотека с названием *s21_decimal.a* (с заголовочным файлом s21_decimal.h);
- Библиотека разработана в соответствии с принципами структурного программирования;
- Выполнено полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check;
- Unit-тесты покрывают не менее 80% каждой функции;  
- Есть Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_decimal.a, gcov_report);
- В цели gcov_report формируется отчёт gcov в виде html страницы. Для этого unit-тесты запускатюся с флагами gcov;  
- Определяемый тип поддерживает числа от -79,228,162,514,264,337,593,543,950,335 до +79,228,162,514,264,337,593,543,950,335.
