#include "gnuplot-iostream.h"

constexpr double RADTODEG = 180. / M_PI;

class Crossover
{
private:
    static std::vector<std::string> filename_;
    static double RI_;
    static double L_  , DL_;
    static double C_  , DC_;
    static double RL_ , DRL_, RIL_, DRIL_;
    static double RC_ , DRC_, RIC_, DRIC_;

public:
    static void add_txt(std::string const& title)
    {
        filename_.push_back(title);
    }

    Crossover(std::string filename)
    {
       add_txt(filename); 
    }

    std::vector<std::string> getFiles() { return filename_; }
    static double getRI()   { return RI_; }
    static double getL()    { return L_; }
    static double getDL()   { return DL_; }
    static double getC()    { return C_; }
    static double getDC()   { return DC_; }
    static double getRL()   { return RL_; }
    static double getDRL()  { return DRL_; }
    static double getRIL()  { return RIL_; }
    static double getDRIL() { return DRIL_; }
    static double getRC()   { return RC_; }
    static double getDRC()  { return DRC_; }
    static double getRIC()  { return RIC_; }
    static double getDRIC() { return DRIC_; }

    static void replace_comma()
    {
        for (auto i : filename_) {
            std::fstream fs(i, std::fstream::in | std::fstream::out);
            if (fs.is_open()) {
                while (!fs.eof()) {
                    if (fs.get() == ',') {
                        fs.seekp((fs.tellp() - static_cast<std::streampos>(1)));
                        fs.put('.');
                        fs.seekp(fs.tellp());
                    }
                }
                fs.close();
            } else {
                std::cout << "Faild to open " << i << '\n';
            }
        }
    }

    static void print_files()
    {
        for (auto i : filename_) {
            std::cout << i << '\n';
        }
    }
};

std::vector<std::string> Crossover::filename_ {};
double Crossover::RI_   = 50.;
double Crossover::L_    = 47.2 * 1e-3;
double Crossover::DL_   = 0.5 * 1e-3;
double Crossover::C_    = 33.2 * 1e-9;
double Crossover::DC_   = 0.3 * 1e-9;
double Crossover::RL_   = 994.;
double Crossover::DRL_  = 5.;
double Crossover::RIL_  = 198.8;
double Crossover::DRIL_ = 0.5;
double Crossover::RC_   = 993.;
double Crossover::DRC_  = 5.;
double Crossover::RIC_  = 201.;
double Crossover::DRIC_ = 1.;

double V_L(double const& nu)
{
    double r = Crossover::getRL() / ( Crossover::getRL() + Crossover::getRIL() );
    double V = 2.395;
    double t_L = Crossover::getL() / ( Crossover::getRL() + Crossover::getRIL() );
    return (r * V) / std::sqrt( 1 + std::pow( 2 * M_PI * nu * t_L, 2 ) );
}

double V_C(double const& nu)
{
    double r = Crossover::getRL() / ( Crossover::getRL() + Crossover::getRIL() );
    double V = 2.395;
    double t_C =  Crossover::getC() * ( Crossover::getRL() + Crossover::getRIL() );
    return (r * V) / std::sqrt( 1 + ( 1 / std::pow( 2 * M_PI * nu * t_C, 2 ) ) );
}

double Ph_L(double const& nu)
{
    double t_L = Crossover::getL() / ( Crossover::getRL() + Crossover::getRIL() );
    return ( - std::atan( 2 * M_PI * t_L * nu * 1 ) * RADTODEG );
}

double Ph_C(double const& nu)
{
    double t_C =  Crossover::getC() * ( Crossover::getRL() + Crossover::getRIL() );
    return ( std::atan( 1 / ( 2 * M_PI * t_C * nu ) ) * RADTODEG );
}

int main()
{
    std::string a, b;
    std::string c {"0.002"};

    std::ifstream fin1     {"Am1_1.txt"};
    std::ofstream foutErr1 {"Am1_1err.txt"};

    std::ifstream fin2     {"Am2_1.txt"};
    std::ofstream foutErr2 {"Am2_1err.txt"};

    std::ifstream fin3     {"Am3_1.txt"};
    std::ofstream foutErr3 {"Am3_1err.txt"};

    std::ifstream fin4     {"Ph2_2.txt"};
    std::ofstream foutErr4 {"Ph22E.txt"};

    std::ifstream fin5     {"Ph3_2.txt"};
    std::ofstream foutErr5 {"Ph32E.txt"};

    std::ofstream fout1 {"VLteo.txt"};
    std::ofstream fout2 {"VCteo.txt"};
    std::ofstream fout3 {"Ph1teo.txt"};
    std::ofstream fout4 {"Ph2teo.txt"};

    while(fin1.good()) {
        fin1 >> a >> b;
        foutErr1 << a << ' ' << b << ' ' << c << '\n';
    }
    fin1.close();
    foutErr1.close();

    while(fin2.good()) {
        fin2 >> a >> b;
        foutErr2 << a << ' ' << b << ' ' << c << '\n';
    }
    fin2.close();
    foutErr2.close();

    while(fin3.good()) {
        fin3 >> a >> b;
        foutErr3 << a << ' ' << b << ' ' << c << '\n';
    }
    fin3.close();
    foutErr3.close();

    while(fin4.good()) {
        fin4 >> a >> b;
        double nu = std::stod(a);
        double dPhi = 180 * nu / 200000;
        foutErr4 << a << ' ' << b << ' ' << dPhi << '\n';
    }
    fin4.close();
    foutErr4.close();

    while(fin5.good()) {
        fin5 >> a >> b;
        double nu = std::stod(a);
        double dPhi = 180 * nu / 200000;
        foutErr5 << a << ' ' << b << ' ' << dPhi << '\n';
    }
    fin5.close();
    foutErr5.close();

    for (int i{}; i != 1e5; ++i) {
        fout1 << static_cast<double>(i) / 10. << ' ' << V_L(static_cast<double>(i) / 10.) << '\n';
        fout2 << static_cast<double>(i) / 10. << ' ' << V_C(static_cast<double>(i) / 10.) << '\n';
        fout3 << static_cast<double>(i) / 10. << ' ' << Ph_L(static_cast<double>(i) / 10.) << '\n';
        fout4 << static_cast<double>(i) / 10. << ' ' << Ph_C(static_cast<double>(i) / 10.) << '\n';
    }
    
    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();

    Crossover::add_txt("FGEN_1k_1.txt");
    Crossover::add_txt("VRC_1k_1.txt");
    Crossover::add_txt("VRL_1k_1.txt");

    Crossover::add_txt("FGEN_4k_1.txt");
    Crossover::add_txt("VRC_4k_1.txt");
    Crossover::add_txt("VRL_4k_1.txt");

    Crossover::add_txt("FGEN_6k_1.txt");
    Crossover::add_txt("VRC_6k_1.txt");
    Crossover::add_txt("VRL_6k_1.txt");

    Crossover::add_txt("FGEN_quad_2.txt");
    Crossover::add_txt("VRC_quad_2.txt");
    Crossover::add_txt("VRL_quad_2.txt");

    Crossover::add_txt("FGEN_quad.txt");
    Crossover::add_txt("VRC_quad.txt");
    Crossover::add_txt("VRL_quad.txt");

    Crossover::add_txt("Am1_1.txt");
    Crossover::add_txt("Am2_1.txt");
    Crossover::add_txt("Am3_1.txt");

    Crossover::add_txt("Am1_2.txt");
    Crossover::add_txt("Am2_2.txt");
    Crossover::add_txt("Am3_2.txt");

    Crossover::add_txt("Fit2_1.txt");
    Crossover::add_txt("Fit3_1.txt");

    Crossover::add_txt("Fit2_2.txt");
    Crossover::add_txt("Fit3_2.txt");

    Crossover::add_txt("Ph1_1.txt");
    Crossover::add_txt("Ph2_1.txt");
    Crossover::add_txt("Ph3_1.txt");

    Crossover::add_txt("Ph1_2.txt");
    Crossover::add_txt("Ph2_2.txt");
    Crossover::add_txt("Ph3_2.txt");

    Crossover::replace_comma();
    // Crossover::print_files();

    Gnuplot gp1;
    gp1 << "set style data lines \n";
    gp1 << "set title \"Crossover Filter - 1000 Hz\" \n";
    gp1 << "set xlabel \"Time [s]\" \n";
    gp1 << "set xrange [0 : 0.005] \n";
    gp1 << "set ylabel \"Amplitude [V]\" \n";
    gp1 << "set yrange [-3 : 3] \n";
    gp1 << "set grid \n";
    gp1 << "plot 'FGEN_1k_1.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'VRC_1k_1.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'VRL_1k_1.txt' t 'Woofer' linecolor rgb \"#0ACE6C\"\n";

    Gnuplot gp2;
    gp2 << "set style data lines \n";
    gp2 << "set title \"Crossover Filter - 4000 Hz\" \n";
    gp2 << "set xlabel \"Time [s]\" \n";
    gp2 << "set xrange [0 : 0.0015] \n";
    gp2 << "set ylabel \"Amplitude [V]\" \n";
    gp2 << "set yrange [-3 : 3] \n";
    gp2 << "set grid \n";
    gp2 << "plot 'FGEN_4k_1.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'VRC_4k_1.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'VRL_4k_1.txt' t 'Woofer' linecolor rgb \"#0ACE6C\"\n";

    Gnuplot gp3;
    gp3 << "set style data lines \n";
    gp3 << "set title \"Crossover Filter - 6000 Hz\" \n";
    gp3 << "set xlabel \"Time [s]\" \n";
    gp3 << "set xrange [0 : 0.001] \n";
    gp3 << "set ylabel \"Amplitude [V]\" \n";
    gp3 << "set yrange [-3 : 3] \n";
    gp3 << "set grid \n";
    gp3 << "plot 'FGEN_6k_1.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'VRC_6k_1.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'VRL_6k_1.txt' t 'Woofer' linecolor rgb \"#0ACE6C\"\n";

    Gnuplot gp4;
    gp4 << "set style data lines \n";
    gp4 << "set title \"Crossover Filter - Quadratic Wave - 1000 Hz\" \n";
    gp4 << "set xlabel \"Time [s]\" \n";
    gp4 << "set autoscale x \n";
    gp4 << "set ylabel \"Amplitude [V]\" \n";
    gp4 << "set yrange [-4.5 : 6] \n";
    gp4 << "set grid \n";
    gp4 << "plot 'FGEN_quad_2.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'VRC_quad_2.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'VRL_quad_2.txt' t 'Woofer' linecolor rgb \"#0ACE6C\"\n";

    Gnuplot gp5;
    gp5 << "set style data lines \n";
    gp5 << "set title \"Frequency Response\" \n";
    gp5 << "set xlabel \"Frequency [Hz]\" \n";
    gp5 << "set ylabel \"Amplitude [V]\" \n";
    gp5 << "set yrange [0.2 : 2.9] \n";
    gp5 << "set xrange [1000 : 10000] \n";
    gp5 << "set grid \n";
    gp5 << "h(x) = ( 25 / 12 ) / sqrt( 1 + ( 2 * pi * H * 1e-9 * x ) ** 2 ) \n";
    gp5 << "fit [1000 : 10000] h(x) 'Am3_1.txt' via H \n";
    gp5 << "k(x) = ( 25 / 12 ) / sqrt( 1 + ( 1 / ( 2 * pi * K * 1e-9 * x ) ** 2 ) ) \n";
    gp5 << "fit [1000 : 10000] k(x) 'Am2_1.txt' via K \n";
    gp5 << "plot 'Am1_1.txt' lw 7 linecolor rgb \"#95FF6C6C\" notitle, "
        << "'Am1_1.txt' t 'FGEN' linecolor rgb \"#FF6C6C\" , "
        << "'Am2_1.txt' lw 7 linecolor rgb \"#95189CFF\" notitle, "
        << "'Am2_1.txt' t 'Tweeter' linecolor rgb \"#189CFF\", "
        << "'Am3_1.txt' lw 7 linecolor rgb \"#950ACE6C\" notitle, "
        << "'Am3_1.txt' t 'Woofer' linecolor rgb \"#0ACE6C\", "
        << "'VCteo.txt' t 'Tweeter Atteso' linecolor rgb \"#00599C\", " 
        << "'VLteo.txt' t 'Woofer Atteso' linecolor rgb \"#108D4F\"\n";

    Gnuplot gp6;
    gp6 << "set style data lines \n";
    gp6 << "set title \"Phase Analysis\" \n";
    gp6 << "set xlabel \"Frequency [Hz]\" \n";
    gp6 << "set xrange [1000 : 10000] \n";
    gp6 << "set ylabel \"Phase [deg]\" \n";
    gp6 << "set yrange [-70 : 80] \n";
    gp6 << "set grid \n";
    gp6 << "f(x) = ( 180 / pi ) * atan( 1 / ( 2 * pi * A * 1e-9 * x ) ) \n";
    gp6 << "fit [1000 : 5000] f(x) 'Ph2_2.txt' via A \n";
    gp6 << "g(x) = - ( 180 / pi ) * atan( 2 * pi * B * 1e-9 * x ) \n";
    gp6 << "fit [1000 : 5000] g(x) 'Ph3_2.txt' via B \n";
    gp6 << "plot 'Ph1_2.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", "
        << "'Ph22E.txt' using 1:($2-$3):($2+$3) with filledcurves linecolor rgb \"#95189CFF\" notitle, "
        << "'Ph32E.txt' using 1:($2-$3):($2+$3) with filledcurves linecolor rgb \"#950ACE6C\" notitle, "
        << "'Ph2_2.txt' t 'Tweeter' linecolor rgb \"#189CFF\", "
        << "'Ph3_2.txt' t 'Woofer' linecolor rgb \"#0ACE6C\", "
        << "'Ph2teo.txt' t 'Tweeter Atteso' linecolor rgb \"#00599C\", "
        << "'Ph1teo.txt' t 'Woofer Atteso' linecolor rgb \"#108D4F\"\n";

    std::cout << "-----------------------------------------\n";
    std::cout << "|    L    =     47.2  +/-  0.5      mH  | \n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|    C    =     33.2  +/-  0.3      nF  | \n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|  R_Ie   =           50           Ohm  | \n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|   R_L   =      994  +/-   5      Ohm  | \n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|   R_C   =      993  +/-   5      Ohm  | \n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|   R_IL  =    198.8  +/-  0.5     Ohm  | \n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|  R_IC   =      201  +/-   1      Ohm  | \n";
    std::cout << "-----------------------------------------\n";
}