# Пишите ваше решение прямо здесь, ниже комментария.
strDays = ["Пн ", "Вт ", "Ср ", "Чт ", "Пт ", "Сб ", "Вс"]

year = 2030
june = "Июнь"
jule = "Июль"
august = "Август"
for i in range(3):
    if i == 0:
        print(year)
        print()
        print(june)
        print()
        for i in range(1):
            print(strDays[0]+strDays[1]+strDays[2]+strDays[3]+strDays[4]+strDays[5]+strDays[6])
        print()
    elif i == 1:
        print(year)
        print()
        print(jule)
        print()
        for i in range(1):
            print(strDays[0]+strDays[1]+strDays[2]+strDays[3]+strDays[4]+strDays[5]+strDays[6])
        print()
    elif i == 2:
        print(year)
        print()
        print(august)
        print()
        for i in range(1):
            print(strDays[0]+strDays[1]+strDays[2]+strDays[3]+strDays[4]+strDays[5]+strDays[6])
        print()
    else:
        print("invalid values")
