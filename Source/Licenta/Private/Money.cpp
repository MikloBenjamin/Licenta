// Fill out your copyright notice in the Description page of Project Settings.


#include "Money.h"

UMoney::UMoney()
{
	Money.Add(1, 5);
	Money.Add(5, 3);
	Money.Add(10, 5);
	Money.Add(20, 4);
	Money.Add(50, 2);
	Money.Add(100, 2);
	Money.Add(500, 1);
	TotalCash = Total();
}

int UMoney::GetTotal() const
{
	return TotalCash;
}

void UMoney::Exchange(const int Amount){
	if(Amount == 500){
		Money[500] -= 1;
		Money[100] += 2;
		Money[50] += 2;
		Money[20] += 5;
		Money[10] += 10;
	} else if(Amount == 100){
		Money[100] -= 1;
		Money[50] += 1;
		Money[20] += 2;
		Money[10] += 1;
	} else if(Amount == 50){
		Money[50] -= 1;
		Money[20] += 1;
		Money[10] += 2;
		Money[5] += 2;
	} else if(Amount == 20){
		Money[20] -= 1;
		Money[10] += 1;
		Money[5] += 1;
		Money[1] += 5;
	} else if(Amount == 10){
		Money[10] -= 1;
		Money[5] += 1;
		Money[1] += 5;
	} else {
		Money[5] -= 1;
		Money[1] += 5;
	}
}

int UMoney::Total()
{
	int Sum = 0;
	Sum += Money[500] * 500;
	Sum += Money[100] * 100;
	Sum += Money[50] * 50;
	Sum += Money[20] * 20;
	Sum += Money[10] * 10;
	Sum += Money[5] * 5;
	Sum += Money[1];
    TotalCash = Sum;
	return Sum;
}

int UMoney::Increase(int Amount){
	const int Initial = Amount;
	TotalCash += Amount;
	if(Amount / 500 > 0){
		Money[500] += Amount / 500;
		Amount = Amount % 500;
	}
	if(Amount / 100 > 0){
		Money[100] += Amount / 100;
		Amount = Amount % 100;
	}
	if(Amount / 50 > 0){
		Money[50] += Amount / 50;
		Amount = Amount % 50;
	}
	if(Amount / 20 > 0){
		Money[20] += Amount / 20;
		Amount = Amount % 20;
	}
	if(Amount / 10 > 0){
		Money[10] += Amount / 10;
		Amount = Amount % 10;
	}
	if(Amount / 5 > 0){
		Money[5] += Amount / 5;
		Amount = Amount % 5;
	}
	if(Amount > 0){
		Money[1] += Amount;
		Amount = 0;
	}
	return Initial;
}

int UMoney::Calculate(const int Amount)
{
	const int Paid = CalcRest(Amount);
	TotalCash = Total();
	return Paid;
}

int UMoney::CalcRest(int ToPay){
    int Initial = ToPay;
    while(ToPay / 500 > 0){
        int ToPayLeft = ToPay / 500;
        while(Money[500] > 0 && ToPayLeft > 0){
            ToPay -= 500;
            Money[500]--;
            ToPayLeft--;
        }
        if(ToPay > 0 || ToPayLeft == 0){
            break;
        }
    }
    while(ToPay / 100 > 0){
        int ToPayLeft = ToPay / 100;
        while(Money[100] > 0 && ToPayLeft > 0){
            ToPay -= 100;
            Money[100]--;
            ToPayLeft--;
        }
        if(ToPayLeft > 0){
            if(Money[500] > 0){
                Exchange(500);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    while(ToPay / 50 > 0){
        int ToPayLeft = ToPay / 50;
        while(Money[50] > 0 && ToPayLeft > 0){
            ToPay -= 50;
            Money[50]--;
            ToPayLeft--;
        }
        if(ToPayLeft > 0){
            if(Money[100] > 0){
                Exchange(100);
            } else if(Money[500] > 0){
                Exchange(500);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    while(ToPay / 20 > 0){
        int ToPayLeft = ToPay / 20;
        while(Money[20] > 0 && ToPayLeft > 0){
            ToPay -= 20;
            Money[20]--;
            ToPayLeft--;
        }
        if(ToPayLeft > 0){
            if(Money[50] > 0){
                Exchange(50);
            }
            else if(Money[100] > 0){
                Exchange(100);
            } else if(Money[500] > 0){
                Exchange(500);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    while(ToPay / 10 > 0){
        int ToPayLeft = ToPay / 10;
        while(Money[10] > 0 && ToPayLeft > 0){
            ToPay -= 10;
            Money[10]--;
            ToPayLeft--;
        }
        if(ToPayLeft > 0){
            if(Money[20] > 0){
                Exchange(20);
            }
            else if(Money[50] > 0){
                Exchange(50);
            }
            else if(Money[100] > 0){
                Exchange(100);
            } else if(Money[500] > 0){
                Exchange(500);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    while(ToPay / 5 > 0){
        int ToPayLeft = ToPay / 5;
        while(Money[5] > 0 && ToPayLeft > 0){
            ToPay -= 5;
            Money[5]--;
            ToPayLeft--;
        }
        if(ToPayLeft > 0){
            if(Money[10] > 0){
                Exchange(10);
            }
            else if(Money[20] > 0){
                Exchange(20);
            }
            else if(Money[50] > 0){
                Exchange(50);
            }
            else if(Money[100] > 0){
                Exchange(100);
            } else if(Money[500] > 0){
                Exchange(500);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    while(ToPay > 0){
        int ToPayLeft = ToPay;
        while(Money[1] > 0 && ToPayLeft > 0){
            ToPay--;
            Money[1]--;
            ToPayLeft--;
        }
        if(ToPayLeft > 0){
            if(Money[5] > 0){
                Exchange(5);
            }
            else if(Money[10] > 0){
                Exchange(10);
            }
            else if(Money[50] > 0){
                Exchange(50);
            }
            else if(Money[100] > 0){
                Exchange(100);
            } else if(Money[500] > 0){
                Exchange(500);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if(ToPay > 0){
        return Initial - ToPay;
    }
    return ToPay;
}
