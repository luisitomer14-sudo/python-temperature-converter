#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Структура для продуктов
struct Product {
    int id;
    string name;
    double price;
};

// Структура для клиента
struct Client {
    string name;
    string address;
    string phone;
};

// Функция для показа главного меню
void showMenu() {
    cout << "\n========================================\n";
    cout << "         ДОСТАВКА ЕДЫ CLI\n";
    cout << "========================================\n";
    cout << "1. Посмотреть рестораны\n";
    cout << "2. Сделать заказ\n";
    cout << "3. Посмотреть мой заказ\n";
    cout << "4. Мои данные (адрес, телефон)\n";
    cout << "5. Подтвердить и выйти\n";
    cout << "========================================\n";
    cout << "Выбор: ";
}

// Функция для показа ресторанов
void showRestaurants() {
    cout << "\n--- ДОСТУПНЫЕ РЕСТОРАНЫ ---\n";
    cout << "1. Пицца Планета\n";
    cout << "2. Суши Экспресс\n";
    cout << "3. Бургер Хаус\n";
}

// Функция для показа меню ресторана
void showRestaurantMenu(int restaurant, vector<Product>& products) {
    cout << "\n--- МЕНЮ ---\n";

    if (restaurant == 1) {
        products = { {1, "Пицца Маргарита", 10.99},
                     {2, "Пицца Пепперони", 12.99},
                     {3, "Пицца Гавайская", 11.99} };
    }
    else if (restaurant == 2) {
        products = { {4, "Калифорния Ролл", 8.99},
                     {5, "Сашими Лосось", 14.99},
                     {6, "Темпура Ролл", 9.99} };
    }
    else {
        products = { {7, "Классический бургер", 7.99},
                     {8, "Двойной бургер", 10.99},
                     {9, "Картошка фри", 3.99} };
    }

    for (const auto& p : products) {
        cout << p.id << ". " << p.name << " - " << p.price << " $\n";
    }
}

// Функция для ввода/редактирования данных клиента
void editClientData(Client& client) {
    cout << "\n========== МОИ ДАННЫЕ ==========\n";
    cout << "Имя: " << client.name << "\n";
    cout << "Адрес: " << (client.address.empty() ? "не указан" : client.address) << "\n";
    cout << "Телефон: " << (client.phone.empty() ? "не указан" : client.phone) << "\n";
    cout << "================================\n";

    cout << "\nХотите изменить данные? (1-Да, 2-Нет): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Введите адрес доставки (улица, дом, квартира): ";
        getline(cin, client.address);

        cout << "Введите номер телефона: ";
        getline(cin, client.phone);

        cout << "\nДанные успешно обновлены!\n";
    }
}

// Функция для проверки заполнения данных клиента
bool checkClientData(const Client& client) {
    if (client.address.empty() || client.phone.empty()) {
        cout << "\nВнимание! У вас не указан адрес или телефон!\n";
        cout << "Пожалуйста, укажите данные в пункте 4 (Мои данные)\n";
        return false;
    }
    return true;
}

int main() {
    Client client;
    vector<Product> cart;
    double total = 0;
    int option;

    // Приветствие
    cout << "\n========================================\n";
    cout << "   ДОБРО ПОЖАЛОВАТЬ В ДОСТАВКУ ЕДЫ\n";
    cout << "========================================\n";
    cout << "Введите ваше имя: ";
    getline(cin, client.name);

    // Запрос адреса при первом входе
    cout << "Введите адрес доставки (улица, дом, квартира): ";
    getline(cin, client.address);

    cout << "Введите номер телефона: ";
    getline(cin, client.phone);

    cout << "\nСпасибо, " << client.name << "!\n";
    cout << "Адрес доставки: " << client.address << "\n";
    cout << "Телефон: " << client.phone << "\n";

    do {
        showMenu();
        cin >> option;

        if (option == 1) {
            // Показать рестораны
            showRestaurants();

            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();

        }
        else if (option == 2) {
            // Сделать заказ
            if (!checkClientData(client)) {
                cout << "\nНажмите Enter для продолжения...";
                cin.ignore();
                cin.get();
                continue;
            }

            int rest, prodId, quantity;
            vector<Product> currentMenu;

            showRestaurants();
            cout << "\nВыберите ресторан (1-3): ";
            cin >> rest;

            if (rest < 1 || rest > 3) {
                cout << "Неверный выбор\n";
                continue;
            }

            showRestaurantMenu(rest, currentMenu);
            cout << "\nВыберите продукт (ID): ";
            cin >> prodId;

            // Поиск продукта
            Product chosenProduct;
            bool found = false;
            for (const auto& p : currentMenu) {
                if (p.id == prodId) {
                    chosenProduct = p;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Продукт не найден\n";
                continue;
            }

            cout << "Количество: ";
            cin >> quantity;

            // Добавить в корзину
            cart.push_back({ chosenProduct.id, chosenProduct.name, chosenProduct.price * quantity });
            total += chosenProduct.price * quantity;

            cout << "\n" << quantity << "x " << chosenProduct.name << " добавлено в корзину!\n";
            cout << "Текущая сумма: " << total << " $\n";

        }
        else if (option == 3) {
            // Посмотреть текущий заказ
            if (cart.empty()) {
                cout << "\nВаша корзина пуста\n";
            }
            else {
                cout << "\n========== ВАШ ЗАКАЗ ==========\n";
                cout << "Клиент: " << client.name << "\n";
                cout << "Адрес доставки: " << client.address << "\n";
                cout << "Телефон: " << client.phone << "\n";
                cout << "--------------------------------\n";

                for (const auto& item : cart) {
                    cout << "  " << item.name << " - " << item.price << " $\n";
                }
                cout << "--------------------------------\n";
                cout << "ИТОГО: " << total << " $\n";
                cout << "================================\n";
            }

        }
        else if (option == 4) {
            // Мои данные
            editClientData(client);

            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();

        }
        else if (option == 5) {
            // Подтвердить заказ
            if (cart.empty()) {
                cout << "\nВы не можете подтвердить пустой заказ!\n";
                cout << "Сначала сделайте заказ (пункт 2)\n";
                option = 0; // Вернуться в меню
            }
            else if (!checkClientData(client)) {
                cout << "\nПожалуйста, укажите адрес и телефон в пункте 4\n";
                cout << "\nНажмите Enter для продолжения...";
                cin.ignore();
                cin.get();
                option = 0;
            }
            else {
                cout << "\n========================================\n";
                cout << "         ЗАКАЗ ПОДТВЕРЖДЕН\n";
                cout << "========================================\n";
                cout << "Клиент: " << client.name << "\n";
                cout << "Адрес доставки: " << client.address << "\n";
                cout << "Телефон: " << client.phone << "\n";
                cout << "----------------------------------------\n";

                for (const auto& item : cart) {
                    cout << "  " << item.name << " - " << item.price << " $\n";
                }

                cout << "----------------------------------------\n";
                cout << "ИТОГО К ОПЛАТЕ: " << total << " $\n";
                cout << "----------------------------------------\n";
                cout << "Время доставки: 30-45 минут\n";
                cout << "Курьер свяжется с вами по телефону\n";
                cout << "========================================\n";
                cout << "\nСпасибо за заказ, " << client.name << "!\n";
                cout << "Приятного аппетита!\n";
            }
        }
        else {
            cout << "\nНеверный выбор. Попробуйте снова.\n";
        }

    } while (option != 5);

    cout << "\nДо свидания, " << client.name << "!\n";
    cout << "Нажмите Enter для выхода...";
    cin.ignore();
    cin.get();

    return 0;
}