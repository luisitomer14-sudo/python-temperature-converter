def celsius_to_fahrenheit(celsius):
    return (celsius * 9/5) + 32

def main():
    print("--- Программа: Конвертер Цельсий -> Фаренгейт ---")
    try:
        c = float(input("Введите температуру в Цельсиях: "))
        f = celsius_to_fahrenheit(c)
        print(f"{c}°C равно {f}°F")
    except ValueError:
        print("Ошибка: пожалуйста, введите числовое значение.")

if __name__ == "__main__":
    main()