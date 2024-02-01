// Фунд(ИДЗ1).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next = nullptr;
};

void List(int n, Node* &head)
{
    Node* end;
    Node* t;
    head = new Node;
    end = head;
    t = head;
    cin >> head->data;
    for (int i{ 0 }; i < n - 1; i++)
    {
        end = new Node;
        cin >> end->data;
        t->next = end;
        t = end;
    }
}

void Print(int n, Node* &head)
{
    Node* end;
    end = head;
    cout << end->data << "   ";
    while (end->next != nullptr)
    {
        end = end->next;
        cout << end->data << "   ";
    }
}

void Deletel(int n, Node* &head) {
    Node* end;
    Node* del;
    end = head;
    if (n == 2) {
        del = end->next;
       free(del);
       free(end);
       //free(head);
       end->next = nullptr;
    }
    else {
        while (end->next != nullptr) {
            end = end->next;
            del = end->next;
            if (del == nullptr) {
                free(del);
                end->next = nullptr;
            }
        }
    }
}

int main()
{
    Node* head;
    int n;
    cin >> n;
    List(n, head);
    Print(n, head);
    cout << "jopa" << endl;
    do {
        Deletel(n, head);
    } while (head->next != nullptr);
    
    cout << &head << endl;



    //Print(n, head);

}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
