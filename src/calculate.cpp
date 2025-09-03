#include "calculate.h"
#include "oreno.h"
#include <string>
#include <cmath>
#include <iostream>
#define QString string
#define QChar char
using namespace std;
QString Calculate(QString RawInput)
{
    int functopnum = 0, firstopnum = 0, veryfirstopnum = 0, lastopnum = 0, opin = -1, startop = 0, endop = 0, next = 0, parannum = 0, innerparannum = 0, paranin = -1;
    QString AraInput = "";
    bool startBabo = false, abesod = true;
    for (int i = 0; i < RawInput.length(); i++)
    {
        if(RawInput[i] == '(' && innerparannum == 0){parannum++; innerparannum++;}
        else if(RawInput[i] == ')' && innerparannum > 0)
        {
            innerparannum--;
        }
        else if(RawInput[i] == '(' && innerparannum > 0){innerparannum++;}
    }
    if(innerparannum != 0){cerr << "Syntax Error\n\n";RawInput = "";}
    for (int i = parannum; i > 0; i--)
    {
        QString IRawInput = "";
        bool inParan = false, isSingle = true;
        int startparan = -1, endparan = -1;
        innerparannum = 0;
        for (int x = 0; x < RawInput.length(); x++)
        {
            if(RawInput[x] == '(' && innerparannum == 0){startBabo = true; innerparannum++; startparan = x;}
            else if(RawInput[x] == ')' && innerparannum > 0)
            {
                innerparannum--;
                if(RawInput[x] == ')' && innerparannum == 0)
                {
                    innerparannum--;
                    endparan = x;
                    startBabo = false;
                    break;
                }
            }
            else if(RawInput[x] == '(' && innerparannum > 0){innerparannum++;}
            if(startBabo && startparan != x){IRawInput += RawInput[x];}
        }
        innerparannum = 0;
        for (int x = 0; x < IRawInput.length(); x++)
        {
            if (IRawInput[x] == '+' || IRawInput[x] == '/' || IRawInput[x] == '*' || IRawInput[x] == '^' || (IRawInput[x] == '-' && x != 0))
            {
                isSingle = false;
            }
        }
        if (isSingle)
        {
            if (IRawInput.length() > 0 && IRawInput[0] == '-')
            {
                IRawInput[0] = '0';
            }
            if (AraInput.length() > 0 && AraInput[AraInput.length() - 1] == '!')
            {
                QString zap = "";
                for (int i = 0; i < IRawInput.length() - 1; i++)
                {
                    zap += IRawInput[i];
                }
                if (TryParse(zap))
                {
                    int ap = stoi(zap);
                    for (int x = ap - 1; x > 1; x--)
                    {
                        ap *= x;
                    }
                    IRawInput = to_string(ap);
                }
                else{cerr << "Syntax Error\n\n"; RawInput = ""; AraInput = "";}
            }
            for (int x = 0; x < RawInput.length(); x++)
            {
                if (x < startparan || x > endparan)
                {
                    AraInput += RawInput[x];
                }
                else if (x == startparan)
                {
                    AraInput += IRawInput;
                }
            }
            RawInput = AraInput;
            AraInput = "";
        }
        else
        {
            for(int x = 0; x < RawInput.length(); x++)
            {
                if(x < startparan || x > endparan)
                {
                    AraInput += RawInput[x];
                }
                else if(x == startparan)
                {
                    AraInput += Calculate(IRawInput);
                }
            }
            RawInput = AraInput;
            AraInput = "";
        }
    }
    for (int i = 0; i < RawInput.length(); i++)
    {
        if (RawInput[i] == '*' || RawInput[i] == '/')
        {
            opin = i;
            firstopnum++;
        }
        else if (RawInput[i] == '+' || (RawInput[i] == '-' && i != 0 && i != opin + 1))
        {
            opin = i;
            lastopnum++;
        }
        else if (RawInput[i] == '^' || RawInput[i] == 'v')
        {
            opin = i;
            veryfirstopnum++;
        }
        else if(RawInput[i] == '!')
        {
            functopnum++;
            opin = i;
        }
    }
    for(int i = functopnum; i > 0; i--)
    {
        bool facto = false;
        QString sum = "";
        for (int x = 0; x < RawInput.length(); x++)
        {
            if (RawInput[x] == '!')
            {
                opin = x;
                facto = true;
                break;
            }
        }
        if (facto)
        {
            endop = opin;
        }
        for (int x = opin - 1; x >= 0; x--)
        {
            if (RawInput[x] == '+' || RawInput[x] == '/' || RawInput[x] == '^' || RawInput[x] == '*' || RawInput[x] == '-' && x > 0)
            {
                if(RawInput[x - 1] != '-')
                {
                    startop = x + 1;
                    break;
                }
            }
            else if(x == 0){startop = 0;}

        }
        for (int x = startop; x < endop; x++)
        {
            sum += RawInput[x];
        }

        for (int x = 0; x < RawInput.length(); x++)
        {
            if (x < startop || x > endop)
            {
                AraInput += RawInput[x];
            }
            else if (x == startop)
            {
                double a, b;
                QString rawx = "", rawy = "";
                QChar op;
                bool xturn = true;
                rawx = sum;
                if (TryParse(rawx) && facto)
                {
                    int sumFact = stoi(rawx);
                    if (sumFact < 0) sumFact = 0;
                    int res = 1;
                    for (int v = sumFact; v > 1; v--)
                    {
                        res *= v;
                    }
                    AraInput += to_string(res);
                }
                else{cerr << "Syntax Error\n\n"; RawInput = ""; AraInput = "";}
            }
        }
        RawInput = AraInput;
        AraInput = "";
        sum = "";
        endop = 0;
        startop = 0;
        opin = 0;
    }
    opin = 0;
    AraInput = "";
    for (int i = veryfirstopnum; i > 0; i--)
    {
        QString sum = "";
        bool squareroot = false;
        for (int x = 0; x < RawInput.length(); x++)
        {
            if (RawInput[x] == '^' || RawInput[x] == 'v')
            {
                if(RawInput[x] == 'v'){squareroot = true;}
                opin = x;
                break;
            }
        }
        for (int x = opin + 1; x < RawInput.length(); x++)
        {
            if (RawInput[x] == '+' || RawInput[x] == '/' || RawInput[x] == '*' || RawInput[x] == '^' || (RawInput[x] == '-' && x != opin + 1))
            {
                endop = x - 1;
                break;
            }
            else if (x == RawInput.length() - 1)
            {
                endop = x;
                break;
            }
        }
        for (int x = opin - 1; x >= 0 && !squareroot; x--)
        {
            if (RawInput[x] == '+' || RawInput[x] == '/' || RawInput[x] == '*' || (RawInput[x] == '-' && x > 0 && RawInput[x - 1] != '-' && x != 0))
            {
                startop = x + 1;
                break;
            }
            else if (x == 0)
            {
                startop = x;
                break;
            }
        }
        if(squareroot){startop = opin;}
        for (int x = startop; x <= endop && !squareroot; x++)
        {
            sum += RawInput[x];
        }
        for(int x = startop + 1; x <= endop && squareroot; x++)
        {
            sum += RawInput[x];
        }
        for (int x = 0; x < RawInput.length(); x++)
        {
            if (x < startop || x > endop)
            {
                AraInput += RawInput[x];
            }
            else if (x == startop && !squareroot)
            {
                double a, b;
                QString rawx, rawy;
                QChar op;
                bool xturn = true;
                for (int q = 0; q < sum.length(); q++)
                {
                    if (sum[q] == '^')
                    {
                        op = sum[q];
                        xturn = false;
                    }
                    else if (xturn)
                    {
                        rawx += sum[q];
                    }
                    else
                    {
                        rawy += sum[q];
                    }
                }
                if (TryParse(rawx) && TryParse(rawy))
                {
                    bool xparanted = false, yparanted = false;
                    if (rawx.length() > 1 && rawx[0] == '0' && rawx != "0" && rawx[1] != '.' && rawx[1] != ',')
                    {
                        rawx[0] = '-';
                    }
                    if (rawy.length() > 1 && rawy[0] == '0' && rawy != "0" && rawy[1] != '.' && rawy[1] != ',')
                    {
                        rawy[0] = '-';
                    }
                    a = stod(rawx);
                    b = stod(rawy);
                    if (b < 0)
                    {
                        double sumch = a;
                        for (int z = abs(b) - 1; z > 0; z--)
                        {
                            sumch *= a;
                        }
                        AraInput += to_string(1 / sumch);
                    }
                    else if (b > 0)
                    {
                        double sumch = a;
                        for (int z = b - 1; z > 0; z--)
                        {
                            sumch *= a;
                        }
                        AraInput += to_string(sumch);
                    }
                    else
                    {
                        AraInput += "1";
                    }
                }
                else{cerr << "Syntax Error\n\n"; RawInput = ""; AraInput = "";}
            }
            else if(x == startop && squareroot)
            {
                if(TryParse(sum)){AraInput += to_string(sqrt(stod(sum)));}
                else{cerr << "Syntax Error\n\n"; RawInput = ""; AraInput = "";}
            }
        }
        RawInput = AraInput;
        AraInput = "";
        sum = "";
        next = 0;
        endop = 0;
        startop = 0;
        opin = 0;
    }
    next = 0;
    opin = 0;
    AraInput = "";
    for (int i = firstopnum; i > 0; i--)
    {
        QString sum = "";
        for (int x = next; x < RawInput.length(); x++)
        {
            if (RawInput[x] == '*' || RawInput[x] == '/')
            {
                opin = x;
                break;
            }
        }
        for (int x = opin + 1; x < RawInput.length(); x++)
        {
            if (RawInput[x] == '+' || RawInput[x] == '/' || RawInput[x] == '*' || (RawInput[x] == '-' && x != opin + 1))
            {
                endop = x - 1;
                break;
            }
            else if (x == RawInput.length() - 1)
            {
                endop = x;
                break;
            }
        }
        for (int x = opin - 1; x >= 0; x--)
        {
            if (RawInput[x] == '+' || RawInput[x] == '/' || RawInput[x] == '*' || RawInput[x] == '-' && x > 0)
            {
                if(RawInput[x - 1] != '-')
                {
                    startop = x + 1;
                    break;
                }
            }
            else if(x == 0){startop = 0;}
        }
        for (int x = startop; x <= endop; x++)
        {
            sum += RawInput[x];
        }
        for (int x = 0; x < RawInput.length(); x++)
        {
            if (x < startop || x > endop)
            {
                AraInput += RawInput[x];
            }
            else if (x == startop)
            {
                double a, b;
                QString rawx = "", rawy = "";
                QChar op;
                bool xturn = true;
                for (int q = 0; q < sum.length(); q++)
                {
                    if (sum[q] == '*' || sum[q] == '/')
                    {
                        op = sum[q];
                        xturn = false;
                    }
                    else if (xturn)
                    {
                        rawx += sum[q];
                    }
                    else
                    {
                        rawy += sum[q];
                    }
                }

                if (TryParse(rawx) && TryParse(rawy))
                {
                    if (rawx.length() > 1 && rawx[0] == '0' && rawx != "0" && rawx[1] != '.' && rawx[1] != ',')
                    {
                        rawx[0] = '-';
                    }
                    if (rawy.length() > 1 && rawy[0] == '0' && rawy != "0" && rawy[1] != '.' && rawy[1] != ',')
                    {
                        rawy[0] = '-';
                    }
                    a = stod(rawx);
                    b = stod(rawy);
                    if (op == '*')
                    {
                        double resultD = a * b;
                        AraInput += to_string(resultD);
                        int absfg = 0;
                    }
                    else
                    {
                        double resultD = a / b;
                        AraInput += to_string(resultD);
                        int absfg = 0;
                    }
                }
                else{cerr << "Syntax Error\n\n"; RawInput = ""; AraInput = "";}
            }
        }
        RawInput = AraInput;
        AraInput = "";
        sum = "";
        next = 0;
        endop = 0;
        startop = 0;
        opin = 0;
    }
    next = 0;
    opin = 0;
    for (int i = lastopnum; i > 0; i--)
    {
        QString sum = "";
        for (int x = next; x < RawInput.length(); x++)
        {
            if (RawInput[x] == '+' || (RawInput[x] == '-' && x != next))
            {
                opin = x;
                break;
            }
        }
        for (int x = opin + 1; x < RawInput.length(); x++)
        {
            if (RawInput[x] == '+' || RawInput[x] == '/' || RawInput[x] == '*' || (RawInput[x] == '-' && x != opin + 1))
            {
                endop = x - 1;
                break;
            }
            else if (x == RawInput.length() - 1)
            {
                endop = x;
                break;
            }
        }
        for (int x = opin - 1; x >= 0; x--)
        {
            if (RawInput[x] == '+' || RawInput[x] == '/' || RawInput[x] == '*' || (RawInput[x] == '-' && x > 0 && RawInput[x - 1] != '-' && x != 0))
            {
                startop = x + 1;
                break;
            }
        }
        for (int x = startop; x <= endop; x++)
        {
            sum += RawInput[x];
        }
        for (int x = 0; x < RawInput.length(); x++)
        {
            if (x < startop || x > endop)
            {
                AraInput += RawInput[x];
            }
            else if (x == startop)
            {
                double a, b;
                QString rawx, rawy;
                QChar op;
                bool xturn = true;
                for (int q = 0; q < sum.length(); q++)
                {
                    if (sum[q] == '+' || (sum[q] == '-' && q != 0 && (q > 0 ? sum[q - 1] != '-' : true)))
                    {
                        op = sum[q];
                        xturn = false;
                    }
                    else if (xturn)
                    {
                        rawx += sum[q];
                    }
                    else
                    {
                        rawy += sum[q];
                    }
                }
                if (TryParse(rawx) && TryParse(rawy))
                {
                    if (rawx.length() > 1 && rawx[0] == '0' && rawx != "0" && rawx[1] != '.' && rawx[1] != ',')
                    {
                        rawx[0] = '-';
                    }
                    if (rawy.length() > 1 && rawy[0] == '0' && rawy != "0" && rawy[1] != '.' && rawy[1] != ',')
                    {
                        rawy[0] = '-';
                    }
                    a = stod(rawx);
                    b = stod(rawy);
                    if (op == '+')
                    {
                        AraInput += to_string(a + b);
                    }
                    else
                    {
                        AraInput += to_string(a - b);
                    }
                }
                else{cerr << "Syntax Error\n\n";}
            }
        }
        RawInput = AraInput;
        AraInput = "";
        sum = "";
        next = 0;
        endop = 0;
        startop = 0;
        opin = 0;
    }
    return RawInput;
}