#include <map>
#include <vector>
#include <iostream>

class ASTCvor
{
public:
    virtual int interpretiraj(std::map<char, int> &mapa) = 0;
    virtual void ispis() = 0;
    virtual ~ASTCvor() = default;
};

class ProgramCvor : public ASTCvor
{
public:
    ProgramCvor() {};

    ~ProgramCvor() = default;

    int interpretiraj(std::map<char, int> &mapa) override
    {
        (void)mapa;
        for (auto naredba : naredbe)
        {
            naredba->interpretiraj(mapa);
        }
        return 0;
    }

    void ispis() override
    {
        for (auto naredba : naredbe)
        {
            naredba->ispis();
            std::cout << '\n';
        }
    }

    void dodaj(ASTCvor *cvor)
    {
        naredbe.push_back(cvor);
    }

private:
    std::vector<ASTCvor *> naredbe;
};

class IdCvor : public ASTCvor
{
public:
    IdCvor(char c) : c(c) {}
    ~IdCvor() {}
    int interpretiraj(std::map<char, int> &mapa) override
    {
        if (mapa.find(c) == mapa.end())
        {
            return -1;
        }
        return mapa[c];
    }

    void ispis() override
    {
        std::cout << c;
    }

    char getChar() { return c; }

private:
    char c;
};

class TrueCvor : public ASTCvor
{
public:
    TrueCvor() {}
    ~TrueCvor() {}
    int interpretiraj(std::map<char, int> &mapa) override
    {
        (void)mapa;
        return 1;
    }

    void ispis() override
    {
        std::cout << "True";
    }
};

class FalseCvor : public ASTCvor
{
public:
    FalseCvor() {}
    ~FalseCvor() {}
    int interpretiraj(std::map<char, int> &mapa) override
    {
        (void)mapa;
        return 0;
    }

    void ispis() override
    {
        std::cout << "False";
    }
};

class KonCvor : public ASTCvor
{
public:
    KonCvor(ASTCvor *l, ASTCvor *r) : l(l), r(r) {}
    ~KonCvor()
    {
        delete l;
        delete r;
    }
    int interpretiraj(std::map<char, int> &mapa) override
    {
        int l1 = l->interpretiraj(mapa);
        int r1 = r->interpretiraj(mapa);
        if (l1 == 0 || r1 == 0)
        {
            return 0;
        }
        if (l1 == 1 && r1 == 1)
        {
            return 1;
        }
        return -1;
    }

    void ispis() override
    {
        l->ispis();
        std::cout << "/\\";
        r->ispis();
    }

private:
    ASTCvor *l, *r;
};

class DisCvor : public ASTCvor
{
public:
    DisCvor(ASTCvor *l, ASTCvor *r) : l(l), r(r) {}
    ~DisCvor()
    {
        delete l;
        delete r;
    }
    int interpretiraj(std::map<char, int> &mapa) override
    {
        int l1 = l->interpretiraj(mapa);
        int r1 = r->interpretiraj(mapa);
        if (l1 == 1 || r1 == 1)
        {
            return 1;
        }
        if (l1 == 0 && r1 == 0)
        {
            return 0;
        }
        return -1;
    }

    void ispis() override
    {
        l->ispis();
        std::cout << "\\/";
        r->ispis();
    }

private:
    ASTCvor *l, *r;
};

class ImpCvor : public ASTCvor
{
public:
    ImpCvor(ASTCvor *l, ASTCvor *r) : l(l), r(r) {}
    ~ImpCvor()
    {
        delete l;
        delete r;
    }
    int interpretiraj(std::map<char, int> &mapa) override
    {
        int l1 = l->interpretiraj(mapa);
        int r1 = r->interpretiraj(mapa);
        if (l1 == 0 || r1 == 1)
        {
            return 1;
        }
        if (l1 == 1 && r1 == 0)
        {
            return 0;
        }
        return -1;
    }

    void ispis() override
    {
        l->ispis();
        std::cout << "=>";
        r->ispis();
    }

private:
    ASTCvor *l, *r;
};

class EkvCvor : public ASTCvor
{
public:
    EkvCvor(ASTCvor *l, ASTCvor *r) : l(l), r(r) {}
    ~EkvCvor()
    {
        delete l;
        delete r;
    }
    int interpretiraj(std::map<char, int> &mapa) override
    {
        int l1 = l->interpretiraj(mapa);
        int r1 = r->interpretiraj(mapa);
        if (l1 != -1 && r1 != -1)
        {
            return l1 == r1;
        }
        return -1;
    }

    void ispis() override
    {
        l->ispis();
        std::cout << "<=>";
        r->ispis();
    }

private:
    ASTCvor *l, *r;
};

class ParCvor : public ASTCvor
{
public:
    ParCvor(ASTCvor *c) : c(c) {}
    ~ParCvor()
    {
        delete c;
    }
    int interpretiraj(std::map<char, int> &mapa) override
    {
        return c->interpretiraj(mapa);
    }

    void ispis() override
    {
        std::cout << '(';
        c->ispis();
        std::cout << ')';
    }

private:
    ASTCvor *c;
};

class NegCvor : public ASTCvor
{
public:
    NegCvor(ASTCvor *c) : c(c) {}
    ~NegCvor()
    {
        delete c;
    }
    int interpretiraj(std::map<char, int> &mapa) override
    {
        int c1 = c->interpretiraj(mapa);
        if (c1 == 1)
        {
            return 0;
        }
        if (c1 == 0)
        {
            return 1;
        }
        return -1;
    }

    void ispis() override
    {
        std::cout << '!';
        c->ispis();
    }

private:
    ASTCvor *c;
};

class DodelaCvor : public ASTCvor
{
public:
    DodelaCvor(IdCvor *l, ASTCvor *r) : l(l), r(r) {}
    ~DodelaCvor()
    {
        delete l;
        delete r;
    }
    int interpretiraj(std::map<char, int> &mapa) override
    {
        char c = l->getChar();
        mapa[c] = r->interpretiraj(mapa);
        return 0;
    }

    void ispis() override
    {
        l->ispis();
        std::cout << ":=";
        r->ispis();
    }

private:
    IdCvor *l;
    ASTCvor *r;
};

class IzrazCvor : public ASTCvor
{
public:
    IzrazCvor(ASTCvor *c) : c(c) {}
    ~IzrazCvor() { delete c; }
    int interpretiraj(std::map<char, int> &mapa) override
    {
        int d = c->interpretiraj(mapa);
        if (d == 1)
        {
            std::cout << "TACNO\n";
        }
        else if (d == 0)
        {
            std::cout << "NETACNO\n";
        }
        else
        {
            std::cout << "NEDEFINISANO\n";
        }
        return d;
    }

    void ispis() override
    {
        c->ispis();
    }

private:
    ASTCvor *c;
};