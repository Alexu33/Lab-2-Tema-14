#ifndef procespenal_h
#define procespenal_h

#include <iostream>
#include "proces.h"
using namespace std;

class ProcesPenal:public Proces
{
private:
    int Dovezi;
    bool Stadiu;
    static int PenalCounter;
public:
    /// constructori si destructori
    ProcesPenal():Proces(),Dovezi(0),Stadiu(0){PenalCounter++;}
    ProcesPenal(int nr, string re, string rec, int dov, bool st):Proces(nr,re,rec),Dovezi(dov),Stadiu(st){PenalCounter++;}
    ~ProcesPenal(){PenalCounter--;cout << "a fost distrus penalul asta" ; Afisare(); cout << endl;}
    ProcesPenal(ProcesPenal &p2)
    {
        SetNrProces(p2.GetNrProces());
        SetReclamant(p2.GetReclamant());
        SetReclamat(p2.GetReclamat());
        Dovezi=p2.Dovezi;
        Stadiu=p2.Stadiu;
    }


    ///functii
    void Afisare();
    void Citire();
    static int GetCounter(){return PenalCounter;};
    static void Init(){PenalCounter=0;};

    /// getteri si setteri
    void SetDovezi(int dov);
    void SetStadiu(bool st);
    int GetDovezi();
    bool GetStadiu();

    ///operatori
    friend ostream& operator << (ostream& os, const ProcesPenal& p);
    friend istream& operator >> (istream& is, ProcesPenal& p);
    void operator = (ProcesPenal &p);

};


///FUNCTII

void ProcesPenal::Afisare()
{
    cout << "Procesul penal " << nrProces << " cu reclamantul " << reclamant << " si reclamatul " << reclamat << " avand stadiul ";
    if(Stadiu==1)
        cout << " activ";
    else
        cout << " inactiv";
    cout <<" cu "<<Dovezi << " dovezi "<<endl<<endl;

}


void ProcesPenal::Citire()
{
    cout << "Citire proces penal: " << endl;
    cout << "NrProces: "; cin>>nrProces;
    cout << "Reclamant: "; cin>>reclamant;
    cout << "Reclamat: "; cin>>reclamat;
    cout << "Nr dovezi: ";cin>>Dovezi;
    if (Dovezi>25)
        Stadiu=1;
    else
        Stadiu=0;
    cout << "Stadiu: "<<Stadiu<<endl<<endl;
}






/// OPERATORI

ostream& operator << (ostream& os, const ProcesPenal& p)
{
    os << "Procesul penal " << p.nrProces << " cu reclamantul " << p.reclamant << " si reclamatul " << p.reclamat << " avand stadiul ";
    if(p.Stadiu==1)
        os << " activ";
    else
        os << " inactiv";
    os <<" cu "<<p.Dovezi << " dovezi "<<endl<<endl;
    return os;
}

istream& operator >> (istream& is, ProcesPenal& p)
{
   cout << "Citire proces penal: " << endl;
    cout << "NrProces: "; is>>p.nrProces;
    cout << "Reclamant: "; is>>p.reclamant;
    cout << "Reclamat: "; is>>p.reclamat;
    cout << "Nr dovezi: ";is>>p.Dovezi;
    if (p.Dovezi>25)
        p.Stadiu=1;
    else
        p.Stadiu=0;
    cout << "Stadiu: "<<p.Stadiu<<endl<<endl;
    return is;
}

void ProcesPenal::operator=(ProcesPenal &p)
{
        SetNrProces(p.GetNrProces());
        SetReclamant(p.GetReclamant());
        SetReclamat(p.GetReclamat());
        Dovezi=p.Dovezi;
        Stadiu=p.Stadiu;
}






/// SETTERI

void ProcesPenal::SetDovezi(int dov)
{
    Dovezi=dov;
}
void ProcesPenal::SetStadiu(bool st)
{
    Stadiu=st;
}




///GETTERI

int ProcesPenal::GetDovezi()
{
    return Dovezi;
}
bool ProcesPenal::GetStadiu()
{
    return Stadiu;
}

int ProcesPenal::PenalCounter=0;





#endif // procespenal_h




