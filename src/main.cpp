#include "gnuplot-iostream.h"

constexpr double RADTODEG = 180. / M_PI;

class Crossover
{
private:
    static std::vector<std::string> filename_;

public:
    static void add_txt(std::string const& title)
    {
        filename_.push_back(title);
    }

    Crossover(std::string filename)
    {
       add_txt(filename); 
    }

    std::vector<std::string> getFiles()
    {
        return filename_;
    }

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

double V_L(double const& nu)
{
    double r = 1000. / 1200.;
    double V = 2.5;
    double t_L = 0.04719 / 1200.;
    return (r * V) / std::sqrt(1 + std::pow( 2 * M_PI * nu * t_L, 2 ) );
}

double V_C(double const& nu)
{
    double r = 1000. / 1200.;
    double V = 2.5;
    double t_C =  33.19 * 1e-9 * 1200.;
    return (r * V) / std::sqrt( 1 + (1 / std::pow( 2 * M_PI * nu * t_C, 2 ) ) );
}

double Ph_L(double const& nu)
{
    double t_L = 0.04719 / 1200.;
    return ( - std::atan( 2 * M_PI * t_L * nu * 1 ) * RADTODEG );
}

double Ph_C(double const& nu)
{
    double t_C =  33.19 * 1e-9 * 1200.;
    return ( std::atan( 1 / (2 * M_PI * t_C * nu) ) * RADTODEG );
}

int main()
{
    std::ofstream fout1 {"VLteo.txt"};
    std::ofstream fout2 {"VCteo.txt"};
    std::ofstream fout3 {"Ph1teo.txt"};
    std::ofstream fout4 {"Ph2teo.txt"};

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
    Crossover::print_files();

    Gnuplot gp1;
    gp1 << "set encoding utf8 \n";
    gp1 << "set style data lines \n";
    gp1 << "set title \"Crossover Filter - 1000 Hz\" \n";
    gp1 << "set xlabel \"Time [s]\" \n";
    gp1 << "set xrange [0 : 0.005] \n";
    gp1 << "set ylabel \"Amplitude [V]\" \n";
    gp1 << "set yrange [-3 : 3] \n";
    gp1 << "set grid \n";
    gp1 << "plot 'FGEN_1k_1.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'VRC_1k_1.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'VRL_1k_1.txt' t 'Woofer' linecolor rgb \"#0ACE6C\"\n";

    Gnuplot gp2;
    gp2 << "set encoding utf8 \n";
    gp2 << "set style data lines \n";
    gp2 << "set title \"Crossover Filter - 4000 Hz\" \n";
    gp2 << "set xlabel \"Time [s]\" \n";
    gp2 << "set xrange [0 : 0.0015] \n";
    gp2 << "set ylabel \"Amplitude [V]\" \n";
    gp2 << "set yrange [-3 : 3] \n";
    gp2 << "set grid \n";
    gp2 << "plot 'FGEN_4k_1.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'VRC_4k_1.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'VRL_4k_1.txt' t 'Woofer' linecolor rgb \"#0ACE6C\"\n";

    Gnuplot gp3;
    gp3 << "set encoding utf8 \n";
    gp3 << "set style data lines \n";
    gp3 << "set title \"Crossover Filter - 6000 Hz\" \n";
    gp3 << "set xlabel \"Time [s]\" \n";
    gp3 << "set xrange [0 : 0.001] \n";
    gp3 << "set ylabel \"Amplitude [V]\" \n";
    gp3 << "set yrange [-3 : 3] \n";
    gp3 << "set grid \n";
    gp3 << "plot 'FGEN_6k_1.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'VRC_6k_1.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'VRL_6k_1.txt' t 'Woofer' linecolor rgb \"#0ACE6C\"\n";

    Gnuplot gp4;
    gp4 << "set encoding utf8 \n";
    gp4 << "set style data lines \n";
    gp4 << "set title \"Crossover Filter - Quadratic Wave - 1000 Hz\" \n";
    gp4 << "set xlabel \"Time [s]\" \n";
    gp4 << "set autoscale x \n";
    gp4 << "set ylabel \"Amplitude [V]\" \n";
    gp4 << "set yrange [-4.5 : 6] \n";
    gp4 << "set grid \n";
    gp4 << "plot 'FGEN_quad_2.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'VRC_quad_2.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'VRL_quad_2.txt' t 'Woofer' linecolor rgb \"#0ACE6C\"\n";

    Gnuplot gp5;
    gp5 << "set encoding utf8 \n";
    gp5 << "set style data lines \n";
    gp5 << "set title \"Frequency Response\" \n";
    gp5 << "set xlabel \"Frequency [Hz]\" \n";
    gp5 << "set ylabel \"Amplitude [V]\" \n";
    gp5 << "set yrange [0.2 : 3] \n";
    gp5 << "set xrange [1000 : 10000] \n";
    gp5 << "set grid \n";
    gp5 << "plot 'Am1_1.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'Am2_1.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'Am3_1.txt' t 'Woofer' linecolor rgb \"#0ACE6C\", 'VCteo.txt' t 'Tweeter Atteso', 'VLteo.txt' t 'Woofer Atteso' \n";

    Gnuplot gp6;
    gp6 << "set encoding utf8 \n";
    gp6 << "set style data lines \n";
    gp6 << "set title \"Phase Analysis\" \n";
    gp6 << "set xlabel \"Frequency [Hz]\" \n";
    gp6 << "set xrange [1000 : 10000] \n";
    gp6 << "set ylabel \"Phase [deg]\" \n";
    gp6 << "set yrange [-60 : 80] \n";
    gp6 << "set grid \n";
    gp6 << "plot 'Ph1_2.txt' t 'FGEN' linecolor rgb \"#FF6C6C\", 'Ph2_2.txt' t 'Tweeter' linecolor rgb \"#189CFF\", 'Ph3_2.txt' t 'Woofer' linecolor rgb \"#0ACE6C\", 'Ph2teo.txt' t 'Tweeter Atteso', 'Ph1teo.txt' t 'Woofer Atteso' \n";
}