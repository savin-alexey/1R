#ifndef TALLER_H
#define TALLER_H

#include <stdlib.h>
#include <string.h>


char* taller(double cost)
{

    char const *kopeck[10] = {"копеек","копейка","копейки","копейки","копейки","копеек","копеек","копеек","копеек","копеек"};
    char const *decades[8] = {"двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
    char const *ruble[10] = {"рублей","рубль","рубля","рубля","рубля","рублей","рублей","рублей","рублей","рублей"};
    char const *hundreds[9] = {"сто","двести","триста","четыреста","пятьсот","шестьсот","семьсот","восемьсот","девятьсот"};
    char const *thousands[9] = {"тысяча","тысячи","тысячи","тысячи","тысяч","тысяч","тысяч","тысяч","тысяч"};
    char const *millions[9] = {"миллион","миллиона","миллиона","миллиона","миллионов","миллионов","миллионов","миллионов","миллионов"};
    char const *numbers_util_20_f[20] = {"ноль","одна","две","три","четыре","пять","шесть","семь","восемь","девять",
                                "десять","одиннадцать","двенадцать","тринадцать","четырнадцать","пятнадцать","шестнадцать","семнадцать","восемнадцать","девятнадцать"};
    char const *numbers_util_20_m[20] = {"ноль","один","два","три","четыре","пять","шесть","семь","восемь","девять",
                                "десять","одиннадцать","двенадцать","тринадцать","четырнадцать","пятнадцать","шестнадцать","семнадцать","восемнадцать","девятнадцать"};


    int decimal_count = 10;
    unsigned long discharge[11] = {0};
    //разбивание на разряды
    unsigned long integer_part = (unsigned long)(cost*1000/10);

    unsigned long buffer;
    while (integer_part != 0)
    {
        buffer = integer_part;
        integer_part /=10;
        discharge[decimal_count] = buffer - integer_part*10;
        decimal_count --;

    }



    //создание сотен и десятков
    int converted_pars[7];
    converted_pars[0] = discharge[0];
    converted_pars[1] = discharge[1]*10 + discharge[2];
    converted_pars[2] = discharge[3];
    converted_pars[3] = discharge[4]*10 + discharge[5];
    converted_pars[4] = discharge[6];
    converted_pars[5] = discharge[7]*10 + discharge[8];
    converted_pars[6] = discharge[9]*10 + discharge[10];



    char *ruble_out = (char*)malloc(256);
    ruble_out[0] = 0;



    char kopeck_out[256] = {};

    int ruble_out_position = -1;
    int millions_out_position = -1;
    int thousands_out_postiton = -1;
    int kopecks_out_postiton = -1;


    //работа с секцией миллионов
    //сотни миллионов
    if ((converted_pars[0]!= 0)&&(converted_pars[0] < 10))
    {
        strncat (ruble_out, hundreds[converted_pars[0]-1],18);
        strncat (ruble_out, " ",2);

        ruble_out_position = 0;
        millions_out_position = 4;
    }
    //если есть десятки миллионов
    if ((converted_pars[1]!= 0)&&(converted_pars[1] <= 99))
    {
        //если дестяки миллионов меньше 20
        if(converted_pars[1] < 20)
        {

            strncat(ruble_out, numbers_util_20_m[converted_pars[1]],24);
            strncat (ruble_out, " ",2);
            if (converted_pars[1] > 3)
                millions_out_position = 4;
            else
                millions_out_position = converted_pars[1]-1;
            ruble_out_position = 0;
        }
        //если дестяки миллионов больше 20
        else
        {
            //заполняем десяток
            strncat(ruble_out, decades[converted_pars[1]/10-2],24);
            if ((converted_pars[1]-converted_pars[1]/10*10) > 0)
            {

                strncat (ruble_out, " ",2);
                strncat(ruble_out, numbers_util_20_m[converted_pars[1]-converted_pars[1]/10*10],24);
                strncat (ruble_out, " ",2);
                millions_out_position = converted_pars[1]-converted_pars[1]/10*10 - 1;
                ruble_out_position = 0;

            }
            else
            {
                strncat (ruble_out, " ",2);
                millions_out_position = 4;
                ruble_out_position = 0;
            }

        }
    }
    if (millions_out_position >= 0)
    {
        strncat (ruble_out, millions[millions_out_position],18);
        strncat (ruble_out, " ",2);
    }

    //работа с секцией тысяч
    //сотни тысяч
    if ((converted_pars[2]!= 0)&&(converted_pars[2] < 10))
    {
        strncat (ruble_out, hundreds[converted_pars[2]-1],18);
        strncat (ruble_out, " ",2);

        ruble_out_position = 0;
        thousands_out_postiton = 4;
    }
    //если есть десятки тысяч

    if ((converted_pars[3]!= 0)&&(converted_pars[3] <= 99))
    {
        //если дестяки тысяч меньше 20
        if(converted_pars[3] < 20)
        {

            strncat(ruble_out, numbers_util_20_f[converted_pars[3]],24);
            strncat (ruble_out, " ",2);
            if (converted_pars[3] > 3)
                thousands_out_postiton = 4;
            else
                thousands_out_postiton = converted_pars[3]-1;
            ruble_out_position = 0;
        }
        //если дестяки тысяч больше 20
        else
        {
            //заполняем десяток
            strncat(ruble_out, decades[converted_pars[3]/10-2],24);
            if ((converted_pars[3]-converted_pars[3]/10*10) > 0)
            {
                strncat (ruble_out, " ",2);
                strncat(ruble_out, numbers_util_20_f[converted_pars[3]-converted_pars[3]/10*10],24);
                strncat (ruble_out, " ",2);
                thousands_out_postiton = converted_pars[3]-converted_pars[3]/10*10 - 1;
                ruble_out_position = 0;

            }
            else
            {
                strncat (ruble_out, " ",2);
                thousands_out_postiton = 4;
                ruble_out_position = 0;
            }

        }
    }
    if (thousands_out_postiton >= 0)
    {
        strncat (ruble_out, thousands[thousands_out_postiton],18);
        strncat (ruble_out, " ",2);
    }

    //работа с сотнями
    //сотни
    if ((converted_pars[4]!= 0)&&(converted_pars[4] < 10))
    {
        strncat (ruble_out, hundreds[converted_pars[4]-1],18);
        strncat (ruble_out, " ",2);

        ruble_out_position = 0;

    }
    //если десятки
    if ((converted_pars[5]!= 0)&&(converted_pars[5] <= 99))
    {
        //если дестяки меньше 20
        if(converted_pars[5] < 20)
        {

            strncat(ruble_out, numbers_util_20_m[converted_pars[5]],24);
            strncat (ruble_out, " ",2);

            ruble_out_position = 0;
        }
        //если дестяки больше 20
        else
        {
            //заполняем десяток
            strncat(ruble_out, decades[converted_pars[5]/10-2],24);
            if ((converted_pars[5]-converted_pars[5]/10*10) > 0)
            {
                strncat (ruble_out, " ",2);
                strncat(ruble_out, numbers_util_20_m[converted_pars[5]-converted_pars[5]/10*10],24);
                strncat (ruble_out, " ",2);
                ruble_out_position = converted_pars[5]-converted_pars[5]/10*10;

            }
            else
            {
                strncat (ruble_out, " ",2);
                ruble_out_position = 0;
            }

        }
    }
    if ((converted_pars[5] == 0)&&(millions_out_position ==-1)&&(thousands_out_postiton == -1)&&(converted_pars[4] == 0))
    {
        strncat(ruble_out, numbers_util_20_m[0],8);
        strncat (ruble_out, " ",2);
        ruble_out_position = 0;
    }

    //работа с копеечками ^_^
    if ((converted_pars[6]!= 0)&&(converted_pars[6] <= 99))
    {
        //если копейки меньше 20
        if(converted_pars[6] < 20)
        {

            strncat(kopeck_out, numbers_util_20_f[converted_pars[6]],24);
            strncat(kopeck_out, " ",2);

            kopecks_out_postiton = 0;
        }
        //если дестяки тысяч больше 20
        else
        {
            //заполняем десяток
            strncat(kopeck_out, decades[converted_pars[6]/10-2],24);
            if ((converted_pars[6]-converted_pars[6]/10*10) > 0)
            {
                strncat (kopeck_out, " ",2);
                strncat(kopeck_out, numbers_util_20_f[converted_pars[6]-converted_pars[6]/10*10],24);
                strncat (kopeck_out, " ",2);
                kopecks_out_postiton = converted_pars[6]-converted_pars[6]/10*10;

            }
            else
            {
                strncat (kopeck_out, " ",2);
                kopecks_out_postiton = 0;
            }

        }
    }
    else
    {
        strncat(kopeck_out, numbers_util_20_f[0],8);
        strncat(kopeck_out, " ",2);
        kopecks_out_postiton = 0;
    }

    strncat(ruble_out, ruble[ruble_out_position],14);
    strncat(ruble_out, " ",2);
    strncat(ruble_out, kopeck_out,256);
    strncat(ruble_out, kopeck[kopecks_out_postiton],14);

    return ruble_out;
}

#endif // TALLER_H
