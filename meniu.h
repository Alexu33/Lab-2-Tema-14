#ifndef meniu_h

#define WINDOWS 1
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>

#include "proces.h"
#include "procescivil.h"
#include "procespenal.h"
using namespace std;


class Meniu
{
private:
    vector<Proces*> ToateProcesele;
public:
    /// FUNCTII
    void Activare();
    void VizualizareProcese();
    void AdaugareProces(string tip);
    Proces* CautareProcesByID(int id);
    void EliminareProces(int id);
    void TaxeTimbru();
    void ClearScreen();
    void ModificareProcesByID(int id);


    /// CONSTRUCTORI SI DESTRUCTORI
    Meniu(){Activare();}
    Meniu(vector<Proces*> a)
    {
        ToateProcesele.clear();
        for(int i=0;i<a.size();i++)
            ToateProcesele.push_back(a[i]);

    }
    Meniu(Meniu &m)
    {
        ToateProcesele.clear();
        for(int i=0;i<m.ToateProcesele.size();i++)
            ToateProcesele.push_back(m.ToateProcesele[i]);
    }
    ~Meniu()
    {
        for(int i=0;i<ToateProcesele.size();i++)
        {
            delete ToateProcesele[i];
        }
        ToateProcesele.clear();
        cout << endl <<"DESTRUCTOR PT MENIU" << endl;
    }


    /// OPERATORI
    friend ostream& operator << (ostream& os, const Meniu& p);
    friend istream& operator >> (istream& is, Meniu& p);
    void operator = (Meniu &p);




};

void Meniu::Activare()
{
    string input="1";
    while(input.compare("0")!=0)
    {
    cout << "ACESTA ESTE MENIUL INTERACTIV: "<<endl;
    cout << "TASTATI NR CORESPUNZATOR PENTRU OPERATIA DORITA"<<endl;
    cout << "1. Vizualizare procese"<<endl; /// ok
    cout << "2. Adaugare proces"<<endl;     /// ok
    cout << "3. Eliminare proces"<<endl;    /// ok
    cout << "4. Taxa de timbru maxima" << endl; /// ok
    cout << "5. Stergere consola"<<endl;    /// ok
    cout << "6. Modificare proces by id"<<endl;     ///upcast, downcast,  static functie pt cautare rapida cica
    cout << "0. Exit"<<endl<<endl;  /// ok
    cout << "INPUT: ";fflush(stdin);cin>>input;
    cout << endl;

    if(input.compare("1")==0)
        VizualizareProcese();
    else if(input.compare("2")==0)
    {
        ClearScreen();
        cout <<"DORITI SA INSERATI UN PROCES:"<<endl;
        cout <<"SELECTATI CE TIP DE PROCES VRETI SA ADAUGATI:"<<endl;
        cout <<"1. Civil"<<endl;
        cout <<"2. Penal"<<endl;
        fflush(stdin);cin>>input;
        if(input.compare("1")==0 || input.compare("2")==0)
            AdaugareProces(input);
        else
        {
            cout << "INPUT INVALID" << endl << endl;
            input="1";
        }
    }
    else if(input.compare("3")==0)
    {
        ClearScreen();
        cout << "INTRUODUCERE ID PROCES PT ELIMINARE: " << endl;
        int id;
        fflush(stdin);
        cin >> id;
        EliminareProces(id);
    }
    else if(input.compare("4")==0)
    {
        if(ProcesCivil::GetCounter()==0)
            cout << "NU EXISTA NICIUN PROCES CIVIL PENTRU A CALCULA TAXA DE TIMBRU" << endl << endl;
        else
            TaxeTimbru();
    }
    else if(input.compare("5")==0)
        ClearScreen();
    else if(input.compare("6")==0)
        {
            ClearScreen();
            cout << "INTRUODUCERE ID PROCES PT ELIMINARE: " << endl;
            int id;
            fflush(stdin);
            cin >> id;
            ModificareProcesByID(id);
        }




    }
    cout << "EXITING PROGRAM"<<endl;
}


void Meniu::VizualizareProcese()
{
    ClearScreen();
    cout <<"VIZUALITATI PROCESE:"<<endl;
    cout <<"1. Toate procesele"<<endl;
    cout <<"2. Proces dupa id"<<endl;
    string tip;
    fflush(stdin);cin >> tip;
    cout << endl;
    if(tip.compare("1")==0)
    {
         if(ToateProcesele.size()==0)
            {
                cout << "Nu exista procese"<<endl<<endl;
                return;
            }

        cout << "Sunt "<< ProcesPenal::GetCounter() << " procese penale" <<endl;
        cout << "Sunt " <<ProcesCivil::GetCounter() << " procese civile" << endl;
        for(int i=0;i<ToateProcesele.size();i++)
                ToateProcesele[i]->Afisare();
    cout << endl << endl;
    }

    else if(tip.compare("2")==0)
    {
        ClearScreen();
        cout << "SCRIETI ID-UL PROCESULUI PE CARE DORITI SA-L GASITI"<<endl;
        int id;
        fflush(stdin);cin >> id;
        Proces *p = CautareProcesByID(id);
        if(p!=NULL)
            p->Afisare();
        else
            cout <<"NU EXISTA PROCESUL CU ID-UL " << id << endl<<endl;
    }
    else
    {
        cout << "INPUT INVALID" << endl;
    }

}


void Meniu::AdaugareProces(string tip)
{
    bool ok=1;
    Proces *p;
    if(tip.compare("1")==0)
    {
        p= new ProcesCivil;
        p->Citire();
    }
    else
        {
            p = new ProcesPenal;
            p->Citire();
        }
    int id;
    id=p->GetNrProces();
    Proces *aux=CautareProcesByID(id);
    if(aux==NULL)
        ok=0;
    if(ok==0)
        ToateProcesele.push_back(p);
    if(ok==1)
    {
        cout << "NU AM PUTUT ADAUGA ACEST PROCES DEOARECE EXISTA ID-UL "<< id<<endl;
    }
}

Proces* Meniu::CautareProcesByID(int id)
{
    int nrcivil,nrpenal;
    nrcivil = ProcesCivil::GetCounter();
    nrpenal = ProcesPenal::GetCounter();

    for(int i=0;i<ToateProcesele.size();i++)
        if(ToateProcesele[i]->GetNrProces() == id)
    {
        return ToateProcesele[i];
    }
    return NULL;
}

void Meniu::ClearScreen()
{
  #ifdef WINDOWS
  system("cls");
  #endif
  #ifdef LINUX
  system("clear");
  #endif
}


void Meniu::EliminareProces(int id)
{
    Proces *p=CautareProcesByID(id);
    if(p==NULL)
    {
        cout <<"NU EXISTA ACEST ID" << endl << endl;
        return;
    }
    for(int i=0;i<ToateProcesele.size();i++)
        if(ToateProcesele[i]==p)
    {
        cout << "STERGERE PROCES CU ID-UL " << id << endl;
        delete ToateProcesele[i];
        ToateProcesele.erase(ToateProcesele.begin()+i);
        return;
    }
}


void Meniu::TaxeTimbru()
{
    double maxim=-1000,aux;
    int id;
    for(int i=0;i<ToateProcesele.size();i++)
        if(ProcesCivil *da = dynamic_cast<ProcesCivil*>(ToateProcesele[i]) )
     if(da->GetStadiu()==1)
        {
            aux=da->TaxaTimbru();
            if(aux>maxim)
                { maxim=aux;id=da->GetNrProces(); }
        }

    if(maxim!= -1000)
        cout << endl << "PROCESUL CU ID-UL " << id << " ARE CEA MAI MARE TAXA DE TIMBRU: " <<maxim << endl << endl;
    else
        cout << "NU EXISTA NICIUN PROCES CIVIL IN STADIUL 1" << endl << endl;

}

void Meniu::ModificareProcesByID(int id)
{
    Proces* p=CautareProcesByID(id);
    if(p==NULL)
    {
        cout << endl<<"NU EXISTA ACEST ID " <<endl;
        return;
    }
    p->Afisare();
    string input;
    cout << endl << endl;
    cout << "URMATOARELE OPERATII DE MODIFICARE SUNT POSIBILE: "<<endl;
    cout << "1. MODIFICARE STADIU" << endl;
    cout << "2. TRANSFORMARE IN CELALALT TIP DE PROCES" << endl;
    cout << "INPUT: "; fflush(stdin); cin >>input;
    if(input.compare("1")==0)
    {
        int aha;
        cout << endl << endl << "INTRODUCETI VALOARE (0 sau 1): "; fflush(stdin); cin >> aha;
        ProcesPenal* aux= dynamic_cast<ProcesPenal*>(p);
        if(aux)
        {
            cout << endl << endl << "ESTE UN PROCES PENAL" << endl;
            aux->SetStadiu(aha);
            aux->Afisare();
        }
        else
        {
            ProcesCivil* pcaux=dynamic_cast<ProcesCivil*>(p);
            cout << endl << endl << "ESTE UN PROCES CIVIL" << endl;
            pcaux->SetStadiu(aha);
            pcaux->Afisare();
        }
        cout << endl << "OPERATIE REALIZATA CU SUCCES" << endl;
    }
    else if(input.compare("2")==0)
    {
        ProcesPenal* verificarepenal = dynamic_cast<ProcesPenal*>(p);
        if(verificarepenal)
        {
            Proces* baza,*procesciv;
            for(int i=0;i<ToateProcesele.size();i++)
                if(ToateProcesele[i]->GetNrProces() == p->GetNrProces())
            {
                ///teste
                if(ProcesPenal* aaa = dynamic_cast<ProcesPenal*>(ToateProcesele[i]))
                {
                    cout << "din test rezulta ca e penal " << endl;
                }
                if(Proces* auxx=dynamic_cast<Proces*>(ToateProcesele[i]))
                {
                    cout << " am reusit sa ii dau upcast"<<endl;
                    baza=new Proces();
                    baza->SetNrProces(auxx->GetNrProces());
                    baza->SetReclamant(auxx->GetReclamant());
                    baza->SetReclamat(auxx->GetReclamat());
                    procesciv=new ProcesCivil();
                    procesciv->SetNrProces(baza->GetNrProces());
                    procesciv->SetReclamant(baza->GetReclamant());
                    procesciv->SetReclamat(baza->GetReclamat());
                }
                delete ToateProcesele[i];
                ToateProcesele.erase(ToateProcesele.begin()+i);
                break;
            }
            /// imi transforma corect in baza
            /*
            if(Proces* as=dynamic_cast<Proces*>(procesciv))
            {
                cout << "Este baza" << endl;
            }
            if(ProcesCivil* as=dynamic_cast<ProcesCivil*>(procesciv))
            {
                cout << "Este civil"<<endl;
            }
            if(ProcesPenal* as=dynamic_cast<ProcesPenal*>(procesciv))
            {
                cout << "Este penal" << endl;
            }
            cout << endl;
            */

            if(ProcesCivil* pc=dynamic_cast<ProcesCivil*>(procesciv))
            {
                cout << "a intrat? " << endl;
                double a;
                int nr;
             cout << "INTRODUCETI NOILE DATE PT PROCESUL CIVIL: " << endl;
             cout << "Daune Morale: "; fflush(stdin); cin >> a; pc->SetDauneMorale(a);
             cout << "Daune Materiale: ";fflush(stdin); cin >> a; pc->SetDauneMateriale(a);
             cout << "Nr Martori: ";fflush(stdin); cin >> nr; pc->SetNrMartori(nr);
             if(nr>5)
                pc->SetStadiu(1);
             else
                pc->SetStadiu(0);
             cout << "Stadiu: " << pc->GetStadiu() << endl << endl;
             ToateProcesele.push_back(pc);

            }

        }
        else /// este civil
        {

            Proces* baza,*procespen;
            for(int i=0;i<ToateProcesele.size();i++)
                if(ToateProcesele[i]->GetNrProces() == p->GetNrProces())
            {
                ///teste
                if(ProcesCivil* aaa = dynamic_cast<ProcesCivil*>(ToateProcesele[i]))
                {
                    cout << "din test rezulta ca e civil " << endl;
                }
                if(Proces* auxx=dynamic_cast<Proces*>(ToateProcesele[i]))
                {
                    cout << " am reusit sa ii dau upcast"<<endl;
                    baza=new Proces();
                    baza->SetNrProces(auxx->GetNrProces());
                    baza->SetReclamant(auxx->GetReclamant());
                    baza->SetReclamat(auxx->GetReclamat());
                    procespen=new ProcesPenal();
                    procespen->SetNrProces(baza->GetNrProces());
                    procespen->SetReclamant(baza->GetReclamant());
                    procespen->SetReclamat(baza->GetReclamat());
                }
                delete ToateProcesele[i];
                ToateProcesele.erase(ToateProcesele.begin()+i);
                break;
            }
            /// imi transforma corect in baza
            /*
            if(Proces* as=dynamic_cast<Proces*>(procesciv))
            {
                cout << "Este baza" << endl;
            }
            if(ProcesCivil* as=dynamic_cast<ProcesCivil*>(procesciv))
            {
                cout << "Este civil"<<endl;
            }
            if(ProcesPenal* as=dynamic_cast<ProcesPenal*>(procesciv))
            {
                cout << "Este penal" << endl;
            }
            cout << endl;
            */

            if(ProcesPenal* pc=dynamic_cast<ProcesPenal*>(procespen))   /// DOWNCAST
            {
                ///cout << "a intrat? " << endl;
                int nr;
             cout << "INTRODUCETI NOILE DATE PT PROCESUL CIVIL: " << endl;
             cout << "Dovezi : "; fflush(stdin); cin >> nr; pc->SetDovezi(nr);
             if(nr>25)
                pc->SetStadiu(1);
             else
                pc->SetStadiu(0);
             cout << "Stadiu: " << pc->GetStadiu() << endl << endl;
             ToateProcesele.push_back(pc);

            }

        }
    }
    else
    {
        cout << endl<<"INPUT INVALID"<<endl;
    }



}



/// OPERATORI

ostream& operator << (ostream& os, const Meniu& p)
{
    if(p.ToateProcesele.size()==0)
        {
            os << "Nu exista procese"<<endl<<endl;
            return os;
        }

    os << "Sunt "<< ProcesPenal::GetCounter() << " procese penale" <<endl;
    os << "Sunt " <<ProcesCivil::GetCounter() << " procese civile" << endl;
    for(int i=0;i<p.ToateProcesele.size();i++)
            p.ToateProcesele[i]->Afisare();
        os << endl << endl;
    return os;
}
 istream& operator >> (istream& is, Meniu& p)
{
    for(int i=0;i<=p.ToateProcesele.size();i++)
        delete p.ToateProcesele[i];
    p.ToateProcesele.clear();

    int n,i;
    string input;
    cout << "CITIRE DE MENIU: " << endl;
    cout << "INTRODUCETI NR DE PROCESE PE CARE VRETI SA-L INSERATI: ";
    fflush(stdin);is>>n;
    for(i=1;i<=n;i++)
    {
        p.ClearScreen();
        cout <<"DORITI SA INSERATI UN PROCES:"<<endl;
        cout <<"SELECTATI CE TIP DE PROCES VRETI SA ADAUGATI:"<<endl;
        cout <<"1. Civil"<<endl;
        cout <<"2. Penal"<<endl;
        fflush(stdin);is>>input;
        if(input.compare("1")==0 || input.compare("2")==0)
            p.AdaugareProces(input);
        else
        {
            cout << "INPUT INVALID" << endl << endl;
            input="1";
        }
    }
    return is;
}
void Meniu::operator = (Meniu &p)
{
    for(int i=0;i<ToateProcesele.size();i++)
        delete ToateProcesele[i];
    ToateProcesele.clear();
    for(int i=0;i<p.ToateProcesele.size();i++)
        ToateProcesele.push_back(p.ToateProcesele[i]);

}


#endif // meniu_h
