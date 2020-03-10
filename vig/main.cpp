#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<ctime>
using namespace std;

const char newline = '\n';
void Setup();
void e_inter(), d_inter(), up_input(string&);
void __attribute__((constructor)) Setup();
string Encrypt(string, string);
string Decrypt(string, string);
string KeyGen(short);
string get_file();
char option;
int Exit_app();
string alfa;
inline void AltEnter(bool&);
void menu();

///********
int main()
{
    menu();
    exit(EXIT_FAILURE);
}

bool isFullScr = false;
string conStat = "fullscreen";
void menu()
{

    cout << "1.encrypt" << newline;
    cout << "2.decrypt" << newline;
    cout << "3." + conStat << newline;
    cout << "4.exit" << newline;
    cout << "alege(1/2/3):";
    option = getch();
    system("cls");
    switch (option)
    {
    case '1':
        e_inter();
        break;
    case '2':
        d_inter();
        break;
    case '3':
        if (!isFullScr)
        {
            conStat = "non" + conStat;
            AltEnter(isFullScr);
        }
        else
        {
            conStat.erase(0, 3);
            AltEnter(isFullScr);
        }
        menu();
        cout << newline;
        break;
    case '4':
        Exit_app();
        break;
    default:
        return menu();
    }
}

void AltEnter(bool& isFullScr)
{
    isFullScr = (!isFullScr) ? true : false;
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void Setup()
{
    ios :: sync_with_stdio(true);
    cin.tie(nullptr);
    cout.tie(nullptr);//*/
    srand(time(NULL));
    system("title V-ENCRYPTER");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);//*/
    for (char c = 'A'; c <= 'Z'; c++)
        alfa += c;
}

int Exit_app()
{
    cout << "Exit";
    for (int i = 0; i < 4; i++)
    {
        Sleep(1000);
        cout << '.';
    }
    exit(EXIT_SUCCESS);
}
///
string Encrypt(string mess, string key)
{
    int i, j, poz, shift;
    string e_mess;
    const int len = mess.size(), key_len = key.size();
    for (i = 0, j = 0; i < len; i++, j++)
    {
        if (mess[i] == 32)
        {
            j--;
            e_mess += 32;
            continue;
        }

        poz = (int)mess[i] - 65;
        shift = (int)key[j % key_len] - 65;
        e_mess += alfa[(shift + poz) % 26];
    }
    return e_mess;
}

string Decrypt(string e_mess, string key)
{
    string text;
    const int len = e_mess.size(), key_len = key.size();
    int i, j, poz, shift;
    for (i = 0, j = 0; i < len; i++, j++)
    {
        if (e_mess[i] == 32)
        {
            j--;
            text += 32;
            continue;
        }
        poz = (int)e_mess[i] - 65;
        shift = (int)key[j % key_len] - 65;
        text += alfa[(poz - shift + 26) % 26];
    }
    return text;
}

string get_file()
{
    system("cls");
    string text = "";
    cout << "Asigurate ca fisieru e in folder cu aplicatia!" << newline;
    string file_name; ///***********
    cout << "Numele fisierului e:";
    cin.ignore();
    getline(cin, file_name);
    fstream fin;
    fin.close();
    fin.open(file_name, ios::in);
    if (!fin.is_open())
    {
        const time_t mili_t = 3000;
        cout << "Eroare!!!";
        Beep((mili_t / 6), mili_t);
        Sleep(mili_t / 3);
        return get_file();
    }
    else
    {
        string line;
        while (getline(fin, line))
            text.append(line);
    }
    fin.close();
    return text;
}

void up_input(string& input)
{
    uint32_t i;
    for (i = 0; i < input.size(); i++)
        input[i] = toupper(input[i]);
}

string KeyGen(short key_len)
{
    string key;
    while (true)
    {
        if (!key_len)
            key_len = rand() % 10;
        for (short i = 0; i < key_len; i++)
            key += alfa[rand() % alfa.size()];

        if (!key.empty())
            break;
    }
    return key;
}

void e_inter()
{
    char ok;
    system("cls");
    char key_type;
    short key_len;
    string key, text;
    cout << "1.Encrypt:" << newline;
    cout << "2.Encrypt file:" << newline;
    do
    {
        option = getch();
    }
    while (key_type < '1' && key_type > '2');
    system("cls");
    cout << "(cheia e cuvant)" << newline;
    cout << "1.Introdu cheia!" << newline;
    cout << "2.Genereaza cheie random!\n";
    do
    {
        key_type = getch();
    }
    while (key_type < '1' && key_type > '2');
    system("cls");
    if (key_type == '2')
    {
        cout << "Lungimea cheii(apasa 0 si enter daca vrei sa fie random):";
        do
        {
            cin >> key_len;
        }
        while (key_len < 0);
        do
        {
            key = KeyGen(key_len);
            cout << "Cheia generata e \"" << key << "\" esti de acord?(0-nu 1-da):";
            ok = getch();
            cout << newline;
        }
        while (ok == '0');
    }
    else
    {
        cout << "Cheie:";
        cin >> key;
    }
    cout << newline;
    if (option == '1')
    {
        cout << "Text:\n";
        cin.ignore();
        getline(cin, text);
    }
    else
    {
        text = get_file();
    }
    up_input(text);
    up_input(key);
    cout << "\nTextul criptat e:" << newline;
    cout << Encrypt(text, key) << newline << newline;
back_interface:
    {
        char opt;
        cout << "1.menu" << newline;
        cout << "2.inapoi" << newline;
        cout << "3.exit" << newline;
        cout << "alege:";
        opt = getch();
        system("cls");
        switch (opt)
        {
        case '1':
            menu();
            break;
        case '2':
            e_inter();
            break;
        case '3':
            Exit_app();
            break;
        default:
            goto back_interface;
        }
    }
}
void d_inter()
{
    string key, e_text;
    cout << "1.decrypt" << newline;
    cout << "2.decrypt file" << newline;
    do
    {
        option = getch();
    }
    while (option < '1' && option > '2');
    system("cls");
    cout << "cheie:";
    cin >> key;
    cin.ignore();
    if (option == '1')
    {
        cout << "Text encriptat:";
        getline(cin, e_text);
    }
    else
    {
        e_text = get_file();
    }
    up_input(key);
    up_input(e_text);
    cout << "Text decriptat:" << newline;
    cout << Decrypt(e_text, key) << newline;
back_interface:
    {
        char opt;
        cout << "1.menu" << newline;
        cout << "2.inapoi" << newline;
        cout << "3.exit" << newline;
        cout << "alege:";
        opt = getch();
        system("cls");
        switch (opt)
        {
        case '1':
            menu();
            break;
        case '2':
            e_inter();
            break;
        case '3':
            Exit_app();
            break;
        default:
            goto back_interface;
        }
    }
}
///****************************************123
