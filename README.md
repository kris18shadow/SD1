# Стуктури от данни и алгоритми - Домашно 1 |(2014г.)

Напишете програма която приема за вход инфиксен израз и файл който описва операторите използвани в изараза и извежда резултата след пресмятане на израза. В израза ще има числа, знаци (оператори) и скоби, като скобите винаги са с най-висок приоритет. Операторите в израза са символи които имат определен приоритет и асоциативност описани във входния фаил в следния формат:

символ оператор приоритет аосциативност
асоциативност: 1 = дясно, 0 = ляво
приоритет: по-голям приоритет = изпълнява се преди тези с по-малък
операторите са тези: +-*/
символът ще бъде операцията в израза
#Пример за файла:

a + 10 1
b + 5 1
c - 5 1
d * 10 1
e / 10 0
f / 10 1

#Пример за израз:

31 a ( 5 b 32 f 10 e -230 ) c 324 d 17
