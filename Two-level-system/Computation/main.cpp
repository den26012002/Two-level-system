#include<fstream>
#include<vector>
#include<complex>

const double hbar = 1;

std::vector<std::pair<double, double>> p_graph_1;
std::vector<std::pair<double, double>> p_graph_2;
double t = 0;
double P1 = 0;
double P2 = 0;

std::complex<double> c_1;
std::complex<double> c_2;

double Omega_R;
double delta;
double omega_0;

double c0_1;
double c0_2;
double omega;
double dt;
double V_0;
double d_12;
double E_0;
double E_1;
double E_2;
double max_time;
double gamma;

void compute() {
    t += dt;

    std::complex<double> dc_1 = (std::complex<double>(-Omega_R, 0) * c_2 * std::exp(std::complex<double>(0, delta * t)) +
        c_1 * std::complex<double>(omega_0, -gamma / 2)) / std::complex<double>(0, 1);

    std::complex<double> dc_2 = (std::complex<double>(-Omega_R, 0) * c_1 * std::exp(std::complex<double>(0, -delta * t)) +
        c_2 * std::complex<double>(omega_0, -gamma / 2)) / std::complex<double>(0, 1);

    c_1 = c_1 + dc_1 * std::complex<double>(dt, 0);
    c_2 = c_2 + dc_2 * std::complex<double>(dt, 0);

    P1 = (c_1 * std::conj(c_1)).real();
    P2 = (c_2 * std::conj(c_2)).real();

    p_graph_1.emplace_back(t, P1);
    p_graph_2.emplace_back(t, P2);
}

void reset() {
    // omega_0 = (E_2 - E_1) / hbar;
    // delta = omega - omega_0;
    c_1 = std::complex<double>(c0_1, 0);
    c_2 = std::complex<double>(c0_2, 0);

    // Omega_R = -d_12 * E_0 / (2.0 * hbar);

    t = 0;

    p_graph_1.clear();
    p_graph_2.clear();
}

void send_data(std::string filename1, std::string filename2) {
    std::ofstream fout1(filename1);
    std::ofstream fout2(filename2);
    for (const auto& dot : p_graph_1) {
        fout1 << dot.first << ' ' << dot.second << '\n';
    }

    for (const auto& dot : p_graph_2) {
        fout2 << dot.first << ' ' << dot.second << '\n';
    }
}

int main() {
    std::ifstream fin("config.txt");
    std::string fieldName;
    fin >> fieldName >> c0_1;
    fin >> fieldName >> c0_2;
    fin >> fieldName >> Omega_R;
    fin >> fieldName >> gamma;
    fin >> fieldName >> dt;
    fin >> fieldName >> max_time;
    // fin >> fieldName >> V_0;
    // fin >> fieldName >> d_12;
    // fin >> fieldName >> E_0;
    // fin >> fieldName >> E_1;
    // fin >> fieldName >> E_2;

    reset();
    while (t < max_time) {
        compute();
    }
    send_data("graph1.txt", "graph2.txt");


	return 0;
}