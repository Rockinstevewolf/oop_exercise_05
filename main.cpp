/*
Создать шаблон динамической коллекцию, согласно варианту задания:
1.   	Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr). Опционально использование std::unique_ptr;
2.   	В качестве параметра шаблона коллекция должна принимать тип данных;
3.   	Реализовать forward_iterator по коллекции;
4.   	Коллекция должны возвращать итераторы begin() и  end();
5.   	Коллекция должна содержать метод вставки на позицию итератора insert(iterator);
6.   	Коллекция должна содержать метод удаления из позиции итератора erase(iterator);
7.   	При выполнении недопустимых операций (например выход аз границы коллекции или удаление не существующего элемента) необходимо генерировать исключения;
8.   	Итератор должен быть совместим со стандартными алгоритмами (например, std::count_if)
9.   	Коллекция должна содержать метод доступа:
            o Стек – pop, push, top; o Очередь – pop, push, top;
            o Список, Динамический массив – доступ к элементу по оператору [];
10.   	Реализовать программу, которая:
            o Позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию;
            o Позволяет удалять элемент из коллекции по номеру элемента; o Выводит на экран введенные фигуры c помощью std::for_each;
            o Выводит на экран количество объектов, у которых площадь меньше заданной (с помощью std::count_if);

Вариант 18: Квадрат, Прямоугольник, Трапеция.

Баранников Степан Алексеевич
M8O-201Б
*/
#include <iostream>
#include <string>
#include <exception>
using namespace std;
#include "Shape.h"
#include "Stack.h"

struct stack_empty : public std::exception
{
    const char* what() const throw ()
    {
        return "The stack is currently empty";
    }
};

void PrintStack(const Stack< Figure<double> >& stack)
{
    int num = 1;
    for_each(stack.begin(), stack.end(), [&num](auto& e)
    {
        cout << num << ". " << e << endl;
        ++num;
    });
}

int GetNum(void)
{
    int k;
    bool got = false;
    while (!got)
    {
        cin >> k;
        if (!cin.good())
        {
            cout << "Bad input ignored:  " << flush;
            cin.clear();
            cin.ignore(256, '\n');
        }
        else got = true;
    }
    return k;
}

void print_menu(){
	cout
	  << "\n1. Add figure\n"
	    << "2. Print all elements\n"
	    << "3. Amount of figures, which have area less than\n"
	    << "4. Print this menu\n"
	    << "5. Delete element\n"
	    << "6. Delete all elements\n"
	    << "0. Exit\n"
	    << flush;
}


int main()
{
	Stack< Figure<double> > fig_stack;
	Figure<double> buff;
	int k = 1;
	size_t num;
	double MaxArea;
	print_menu();
	do{
		cout << "---------------\n> ";
		try{
			k = GetNum();
			if(!cin) throw runtime_error("Failed to get input");
			switch (k){
				case 1:
				    cin >> buff;
				    fig_stack.push(buff);
				    k = 1;
				    break;
				case 2:
				    if (fig_stack.empty()) throw stack_empty();
				    PrintStack(fig_stack);
				    break;
				case 3:
				    if (fig_stack.empty()) throw stack_empty();
				    cout << "Max area: ";
				    cin >> MaxArea;
				    cout << "The amount of Figures that are equal or lower is " << count_if( fig_stack.begin(), fig_stack.end(), [&MaxArea](auto& fig) -> bool
				        {
				            return ( !fig.Abstract && (fig.area < MaxArea || DoubleEqual(fig.area, MaxArea)) );
				        }
				    ) << endl;
				    break;
				case 4:
				    print_menu();
				    break;
				case 5:
				    if (fig_stack.empty()) throw stack_empty();
				    cout << "Number of the Figure: ";
				    num = GetNum();
				    if (num < 1 || num > fig_stack.size()) throw runtime_error("Incorrect index");
				    fig_stack.erase(num - 1);
				    break;
				case 6:
				    fig_stack.erase();
				    cout << "Stack erased" << endl;
				    break;
				case 0:
				    break;
				default:
				    cout << "No such number" << endl;
			}
		}

		catch (stack_empty& err)
		{
		    cout << err.what() << endl;
		}
		catch (runtime_error& err)
		{
		    cerr << err.what() << endl;
		}
		catch (logic_error & err)
		{
		    cerr << "In stack: " << err.what() << endl;
		}
		catch (...)
		{
		    cerr << "Exception thrown, but undefined. Please open an issue at GitHub with steps to reproduce ." << endl;
		}
	} while (k);
	return 0;
}
