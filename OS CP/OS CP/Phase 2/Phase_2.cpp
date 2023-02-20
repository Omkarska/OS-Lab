#include <bits/stdc++.h>
using namespace std;

string IPFILE = "job.txt";

char Memory[300][4];
vector<char> R(4), IR(4);
int IC = 0, SI = 3, job = 1, PI = 0, TI = 0, cnt = 0, TTL = 0, LineLImit = 0, PTR = 0, Fill, EM = 0;
int input_ptr = 0, output_ptr = 0;
bool C = false;
string buffer = "";
set<int> random_numbers;

void print_mem();
void clearContents();
void lineReader(string temp);
void READ(int block);
void WRITE(int block);
int TERMINATE(int si);
int AddressMap(int VA);
void executeUserProgram();
void startExecution();
void SetPageTable(int PTR);
void LOAD();
void endExecution(int TTC, int TLC);

struct PCB
{
    int TTL, TLL, TTC, TLC;
};
struct PCB jobs[10];

void endExecution(int TTC, int TLC)
{
    fstream fout;
    fout.open("output.txt");
    fout.seekg(0, ios::end);
    if (EM == 0)
    {
        cout << "program terminated normally";
        fout << "\nSI = " << SI << "  TI =" << TI << "  PI=" << PI << endl;
        fout << "TTC = " << TTC << "  LLC=" << TLC << endl;
        cout << "\nSI = " << SI << "  TI =" << TI << "  PI=" << PI << endl;
        cout << "TTC = " << TTC << "  LLC=" << TLC << endl;
        fout << endl
             << "program terminated normally" << endl
             << endl;
        fout.close();
        return;
    }
    fout << "\nSI = " << SI << "  TI =" << TI << "  PI=" << PI << endl;
    fout << "TTC = " << TTC << "  LLC=" << TLC << endl;
    cout << "\nSI = " << SI << "  TI =" << TI << "  PI=" << PI << endl;
    cout << "TTC = " << TTC << "  LLC=" << TLC << endl;
    fout << endl;
}

void print_mem()
{
    cout << "Memory for job " << job << "\n";
    for (int i = 0; i < 300; i++)
    {
        for (int k = 0; k < 4; k++)
        {
            cout << Memory[i][k] << " ";
        }
        cout << endl;
    }
}

void clearContents()
{
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Memory[i][j] = '_';
        }
    }
    buffer.clear();
    R.clear();
    random_numbers.clear();
    IC = 0;
    C = false;
}

void lineReader(string temp)
{
    jobs[cnt].TLC++;
    fstream fout;
    fout.open("output.txt");
    fout.seekg(0, ios::end);
    fout << temp;
    fout << "\n";
    fout.close();
}

void READ(int block)
{
    fstream fin;
    string line;
    fin.open(IPFILE, ios::in);
    for (int i = 0; i < input_ptr; i++)
    {
        getline(fin, line);
    }
    getline(fin, line);
    input_ptr++;
    fin.close();

    buffer = line;
    for (int i = 0; i < buffer.size() && i < 40; i++)
    {
        int a = i / 4 + block;
        int b = i % 4;
        Memory[a][b] = buffer[i];
    }
}

void WRITE(int block)
{
    string temp = "";
    int i = 0;
    while (i < 40)
    {
        int a = i / 4 + block;
        int b = i % 4;
        if (Memory[a][b] == '_')
        {
            temp.push_back(' ');
        }
        else
            temp.push_back(Memory[a][b]);
        i++;
    }

    lineReader(temp);
}

int TERMINATE(int si)
{
    if (si == 3)
        return 1;
    else
        return 0;
}

int AddressMap(int VA)
{

    int RA;
    int PTE = PTR + VA / 10;
    if (Memory[PTE][2] == '*' || Memory[PTE][3] == '*')
    {
        PI = 3;
        bool flag = true;
        int Entry = rand() % 30;
        if (random_numbers.find(Entry * 10) == random_numbers.end())
        {
            random_numbers.insert(Entry * 10);
        }
        else
        {
            while (random_numbers.find(Entry * 10) != random_numbers.end())
            {
                Entry = rand() % 30;
            }
        }

        string EntryStr = to_string(Entry);

        if (EntryStr.size() == 1)
        {
            Memory[PTE][2] = '0';
            Memory[PTE][3] = EntryStr[0];
        }
        else
        {
            Memory[PTE][2] = EntryStr[0];
            Memory[PTE][3] = EntryStr[1];
        }

        RA = Entry * 10 + VA % 10;
    }

    else
    {
        string t = "";
        t.push_back(Memory[PTE][2]);
        t.push_back(Memory[PTE][3]);
        int no = stoi(t);
        RA = no * 10 + VA % 10;
    }

    return RA;
}

void executeUserProgram()
{
    vector<string> ins = {"GD", "PD", "CR", "SR", "LR", "BT"};

    while (1)
    {
        jobs[cnt].TTC++;
        string Opc_ins = "", Opr_ins = "";
        for (int i = 0; i < 4; i++)
        {
            IR[i] = Memory[IC][i];
        }
        if (IR[0] == 'H')
        {
            TERMINATE(SI);
            break;
        }
        if (IR[2] == '-' || isdigit(IR[0]) || isalpha(IR[2]) || isalpha(IR[3]))
        {
            PI = 2;
            break;
        }
        Opc_ins += Memory[IC][0];
        Opc_ins += Memory[IC][1];
        if (find(ins.begin(), ins.end(), Opc_ins) == ins.end())
        {
            PI = 1;
            break;
        }
        int t1 = ((int)IR[2]) - ((int)'0');
        int t2 = ((int)IR[3]) - ((int)'0');
        int block = t1 * 10 + t2;
        int RealAdd = AddressMap(block);
        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            READ(RealAdd);
            jobs[cnt].TTC++;
        }

        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            WRITE(RealAdd);
        }

        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            cout << "\n"
                 << endl;

            for (int i = 0; i < 4; i++)
            {
                R[i] = Memory[RealAdd][i];
            }
        }

        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            bool f = 0;

            for (int i = 0; i < 4; i++)
            {
                if (R[i] != Memory[RealAdd][i])
                {
                    f = 1;
                    break;
                }
            }

            if (f)
                C = false;
            else
                C = true;
        }

        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            for (int j = 0; j < 4; j++)
            {
                Memory[RealAdd][j] = R[j];
            }
            jobs[cnt].TTC++;
        }

        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            if (C == true)
            {
                IC = RealAdd - 1;
            }
        }
        IC++;
    }
}

void startExecution()
{
    IC = Fill;
    executeUserProgram();
    fstream fout;
    fout.open("output.txt");
    fout.seekg(0, ios::end);
    fout << "\n\n";
    fout.close();
}

void SetPageTable(int PTR)
{
    for (int i = 0; i < 10; i++)
    {
        Memory[PTR + i][0] = '*';
        Memory[PTR + i][1] = '*';
        Memory[PTR + i][2] = '*';
        Memory[PTR + i][3] = '*';
    }
}

void LOAD()
{
    fstream fin;
    string line;
    while (1)
    {
        EM = 0;
        fin.open(IPFILE, ios::in);
        for (int j = 0; j < input_ptr; j++)
        {
            getline(fin, line);
        }

        getline(fin, line);
        input_ptr++;
        fin.close();

        if (line.substr(0, 4) == "$END")
            break;

        if (line.substr(0, 4) == "$AMJ")
        {
            PI = 0;
            clearContents();
            TTL = stoi(line.substr(8, 4));

            LineLImit = stoi(line.substr(12, 4));

            struct PCB CJob;
            CJob.TTL = TTL;
            CJob.TLL = LineLImit;
            CJob.TTC = 0;
            CJob.TLC = 0;
            jobs[cnt] = CJob;

            PTR = rand() % 30;

            PTR = PTR * 10;
            for (int i = PTR; i < (PTR + 11); i++)
            {
                random_numbers.insert(i);
            }

            SetPageTable(PTR);

            int First_Entry = rand() % 30;

            string FE = to_string(First_Entry);
            if (FE.size() == 1)
            {
                Memory[PTR][2] = '0';
                Memory[PTR][3] = FE[0];
            }
            else
            {
                Memory[PTR][2] = FE[0];
                Memory[PTR][3] = FE[1];
            }

            Fill = First_Entry * 10;
            random_numbers.insert(Fill);

            string prog;
            fin.open(IPFILE, ios::in);
            for (int j = 0; j < input_ptr; j++)
            {
                getline(fin, prog);
            }
            getline(fin, prog);
            input_ptr++;

            int k = Fill;
            int b = 0, rw = 0;
            while (prog.substr(0, 4) != "$DTA")
            {

                for (int j = 0; j < prog.size(); j++)
                {
                    random_numbers.insert(k);
                    if (prog[j] == 'H')
                    {
                        Memory[k][0] = 'H';
                        k++;
                        continue;
                    }

                    else
                    {
                        Memory[k][b] = prog[j];
                        rw++;
                    }
                    if (rw % 4 == 0)
                    {
                        k++;
                        b = -1;
                        rw = 0;
                    }
                    b++;
                }

                getline(fin, prog);

                input_ptr++;
            }

            getline(fin, prog);

            if (prog.substr(0, 4) == "$END")
            {
                cout << "Out of Data Error! \n";
                EM = 1;
                endExecution(jobs[cnt].TTC, jobs[cnt].TLC);
            }

            fin.close();

            startExecution();

            if (jobs[cnt].TTL < jobs[cnt].TTC)
            {
                fstream fout;
                fout.open("output.txt");
                fout.seekg(0, ios::end);
                TI = 2;
                cout << "Time Limit Exceeded! It took " << jobs[cnt].TTC << " units of time. Expected TTL was " << jobs[cnt].TTL << "\n"
                     << "Program terminated abnormally" << endl;
                fout << "Time Limit Exceeded! It took " << jobs[cnt].TTC << " units of time. Expected TTL was " << jobs[cnt].TTL << "\n"
                     << "Program terminated abnormally" << endl;
                EM = 3;
                endExecution(jobs[cnt].TTC, jobs[cnt].TLC);
                fout.close();
            }

            else if (jobs[cnt].TLL < jobs[cnt].TLC)
            {
                fstream fout;
                fout.open("output.txt");
                fout.seekg(0, ios::end);
                cout << "Line Limit Exceeded! It printed " << jobs[cnt].TLC << " lines. Expected Line Limit was " << jobs[cnt].TLL << "\n"
                     << "Program terminated abnormally" << endl;
                fout << "Line Limit Exceeded! It printed " << jobs[cnt].TLC << " lines. Expected Line Limit was " << jobs[cnt].TLL << "\n"
                     << "Program terminated abnormally" << endl;
                EM = 2;
                endExecution(jobs[cnt].TTC, jobs[cnt].TLC);
                fout.close();
            }

            else if (PI == 1)
            {
                fstream fout;
                fout.open("output.txt");
                fout.seekg(0, ios::end);
                cout << "Opcode Error \n"
                     << "Program terminated abnormally" << endl;
                cout << "Job No " << job << " is not executed \n";
                fout << "Opcode Error \n"
                     << "Program terminated abnormally" << endl;
                fout << "Job No " << job << " is not executed \n";
                EM = 4;
                endExecution(jobs[cnt].TTC, jobs[cnt].TLC);
                fout.close();
            }
            else if (PI == 2)
            {
                fstream fout;
                fout.open("output.txt");
                fout.seekg(0, ios::end);
                cout << "Operand Error \n"
                     << "Program terminated abnormally" << endl;
                cout << "Job No " << job << " is not executed \n";
                fout << "Operand Error \n"
                     << "Program terminated abnormally" << endl;
                fout << "Job No " << job << " is not executed \n";
                EM = 5;
                endExecution(jobs[cnt].TTC, jobs[cnt].TLC);
                fout.close();
            }
            else
            {
                print_mem();
                endExecution(jobs[cnt].TTC, jobs[cnt].TLC);
            }
            job++;
            cnt++;
        }

        fin.open(IPFILE, ios::in);
        for (int j = 0; j < input_ptr; j++)
        {
            getline(fin, line);
        }
        getline(fin, line);
        input_ptr++;

        while (line.substr(0, 4) != "$END")
        {
            getline(fin, line);
            input_ptr++;
        }
        getline(fin, line);
    }
    fin.close();
}

int main()
{
    LOAD();
    return 0;
}
