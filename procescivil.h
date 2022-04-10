#ifndef procescivil_h
#define procescivil_h

#include <iostream>
#include "proces.h"

using namespace std;

class ProcesCivil:public Proces
{
private:
    double DauneMorale;
    double DauneMateriale;
    int NrMartori;
    bool Stadiu;
    static int CivilCounter;
public:
    /// constructori si destructori
    ProcesCivil():Proces(),DauneMorale(0),DauneMateriale(0),NrMartori(0),Stadiu(0){CivilCounter++;}
    ProcesCivil(int nr, string re, string rec, double dmo, double dma, int nrm):Proces(nr,re,rec),DauneMorale(dmo),DauneMateriale(dma),NrMartori(nrm),Stadiu(0){if(NrMartori>5)Stadiu=1; CivilCounter++;}
    ~ProcesCivil(){CivilCounter--; cout << "a fost distrus civilul asta" << endl; Afisare(); cout << endl;}
    ProcesCivil(ProcesCivil &p)
    {
        SetNrProces(p.GetNrProces());
        SetReclamant(p.GetReclamant());
        SetReclamat(p.GetReclamat());
        DauneMorale=p.DauneMorale;
        DauneMateriale=p.DauneMateriale;
        NrMartori=p.NrMartori;
        Stadiu=p.Stadiu;
    }

    /// functii
    double TaxaTimbru();
    void Afisare();
    void Citire();
    static int GetCounter(){return CivilCounter;};
    static void Init(){CivilCounter=0;};

    /// getteri si setteri
    void SetStadiu(bool ok);
    void SetNrMartori(int nr);
    void SetDauneMateriale(double dm);
    void SetDauneMorale(double dm);
    bool GetStadiu();
    int GetNrMartori();
    double GetDauneMateriale();
    double GetDauneMorale();


    /// operatori
    friend ostream& operator << (ostream& os, const ProcesCivil& pc);
    friend istream& operator >> (istream& is, ProcesCivil& pc);
    void operator = (ProcesCivil &p);
};


///OPERATORI
ostream& operator << (ostream& os, const ProcesCivil& pc)
{
    os << "Procesul civil " << pc.nrProces << " cu reclamantul " << pc.reclamant << " si reclamatul " << pc.reclamat << " avand stadiul";
    if(pc.Stadiu==1)
        os << " activ";
    else
        os << " inactiv";
    os <<" cu "<<pc.NrMartori << " martori cu daune morale in valoare de "<<pc.DauneMorale<< " si daune materiale in valoare de " << pc.DauneMateriale<< endl<<endl;
    return os;
}

istream& operator >> (istream& is, ProcesCivil& pc)
{
    cout << "Citire proces civil: " << endl;
    cout << "NrProces: "; is>>pc.nrProces;
    cout << "Reclamant: "; is>>pc.reclamant;
    cout << "Reclamat: "; is>>pc.reclamat;
    cout << "Daune Morale: "; is >>pc.DauneMorale;
    cout << "Daune Materiale: "; is >> pc.DauneMateriale;
    cout << "Nr Martori: "; is >> pc.NrMartori;
    if(pc.NrMartori>5)
        pc.Stadiu=1;
    else
        pc.Stadiu=0;
    cout << "Stadiu: "<<pc.Stadiu<<endl<<endl;
    return is;
}

void ProcesCivil::operator=(ProcesCivil &p)
{
        SetNrProces(p.GetNrProces());
        SetReclamant(p.GetReclamant());
        SetReclamat(p.GetReclamat());
        DauneMorale=p.DauneMorale;
        DauneMateriale=p.DauneMateriale;
        NrMartori=p.NrMartori;
        Stadiu=p.Stadiu;
}





/// FUNCTII
double ProcesCivil::TaxaTimbru()
{
   return (0.1 * DauneMorale + 0.1* DauneMateriale);
}

void ProcesCivil::Afisare()
{

    cout << "Procesul civil " << nrProces << " cu reclamantul " << reclamant << " si reclamatul " << reclamat << " avand stadiul";
    if(Stadiu==1)
        cout << " activ";
    else
        cout << " inactiv";
    cout <<" cu "<<NrMartori << " martori cu daune morale in valoare de "<<DauneMorale<< " si daune materiale in valoare de " << DauneMateriale<< endl<<endl;

}

void ProcesCivil::Citire()
{
    cout << "Citire proces civil: " << endl;
    cout << "NrProces: "; cin>>nrProces;
    cout << "Reclamant: "; cin>>reclamant;
    cout << "Reclamat: "; cin>>reclamat;
    cout << "Daune Morale: "; cin >>DauneMorale;
    cout << "Daune Materiale: "; cin >> DauneMateriale;
    cout << "Nr Martori: "; cin >> NrMartori;
    if (NrMartori>5)
        Stadiu=1;
    else
        Stadiu=0;
    cout << "Stadiu: "<<Stadiu<<endl<<endl;
}

///SETTERI
void ProcesCivil::SetDauneMateriale(double dm)
{
    DauneMateriale=dm;
}
void ProcesCivil::SetDauneMorale(double dm)
{
    DauneMorale=dm;
}
void ProcesCivil::SetNrMartori(int nr)
{
    NrMartori=nr;
}
void ProcesCivil::SetStadiu(bool ok)
{
    Stadiu=ok;
}


/// GETTERI
double ProcesCivil::GetDauneMateriale()
{
    return DauneMateriale;
}
double ProcesCivil::GetDauneMorale()
{
    return DauneMorale;
}
int ProcesCivil::GetNrMartori()
{
    return NrMartori;
}
bool ProcesCivil::GetStadiu()
{
    return Stadiu;
}

int ProcesCivil::CivilCounter=0;





#endif // procescivil_h

