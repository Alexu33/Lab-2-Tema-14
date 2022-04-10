#ifndef forma_h
#define forma_h

#include <iostream>
using namespace std;

class Proces
{
protected:
    int nrProces;
    string reclamant;
    string reclamat;

public:
    ///constructori si destructori
    Proces(int a, string b, string c): nrProces(a), reclamant(b), reclamat(c){cout <<"const" << endl;}
    Proces():nrProces(-1),reclamant("necunoscut"),reclamat("necunoscut"){cout << "constructor"<<endl;}
    virtual ~Proces(){cout << "a fost distrus normalul asta "; cout << endl;}
    Proces(const Proces &p2)
    {
        nrProces=p2.nrProces;
        reclamant=p2.reclamant;
        reclamat=p2.reclamat;
    }

    ///functii
    int GetNrProces();
    void SetNrProces(int aux);
    string GetReclamant();
    void SetReclamant(string aux);
    string GetReclamat();
    void SetReclamat(string aux);

    /// virtual
    virtual void Afisare();
    virtual void Citire();


    /// operatori
    friend ostream& operator << (ostream& os, const Proces& p);
    friend istream& operator >> (istream& is, Proces& p);
    void operator = (const Proces& p);

};


int Proces::GetNrProces()
{
    return nrProces;
}

void Proces::SetNrProces(int aux)
{
    nrProces=aux;
}
string Proces::GetReclamant()
{
    return reclamant;
}
void Proces::SetReclamant(string aux)
{
    reclamant=aux;
}
string Proces::GetReclamat()
{
    return reclamat;
}
void Proces::SetReclamat(string aux)
{
    reclamat=aux;
}

/// operatori

ostream& operator<<(ostream& os, const Proces& p)
{
    os << "Procesul " << p.nrProces << " cu reclamantul " << p.reclamant << " si reclamatul " << p.reclamat << endl<<endl;
    return os;
}
istream& operator >> (istream& is, Proces& p)
{
    cout << "Citire proces normal: " << endl;
    cout << "NrProces: "; is>>p.nrProces;
    cout << "Reclamant: "; is>>p.reclamant;
    cout << "Reclamat: "; is>>p.reclamat;
    cout << endl;
    return is;
}




/// virtual
void Proces::Afisare()
{
    cout << "Procesul normal " << nrProces << " cu reclamantul " << reclamant << " si reclamatul " << reclamat << endl<<endl;
}
void Proces::Citire()
{
    cout << "Citire proces normal: " << endl;
    cout << "NrProces: "; cin>>nrProces;
    cout << "Reclamant: "; cin>>reclamant;
    cout << "Reclamat: "; cin>>reclamat;
    cout << endl;
}

void Proces::operator=(const Proces& p)
{
    nrProces=p.nrProces;
    reclamant=p.reclamant;
    reclamat=p.reclamat;
}



#endif


