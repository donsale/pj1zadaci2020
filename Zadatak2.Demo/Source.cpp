#include <set>

#include "ComparableVectorN.h"
#include "OrderedVectorSetN.h"
#include "VectorN.h"
#include "VectorSetN.h"

using namespace zadatak2;

double ManhattanDistance(const VectorN& vec) {
  double sum = 0;
  for (size_t i = 0; i < vec.getSize(); i++) sum += std::abs(vec[i]);
  return sum;
}

int main() {
  // VectorN
  // Omogućiti nasumični pristup elementima niza korištenjem odgovarajućih
  // metoda
  VectorN v{1.5, 2.5, 3.55};
  double a = v[0];

  // Obezbijediti imutabilnost objekata(individualni elementi vektora ne smiju
  // se mijenjati) v[0] = 5.5;  greška!

  // Onemogućiti pristup izvan opsega niza proizvoljnim mehanizmom.  Koristiti
  // odgovarajući operator za pristup elementima.
  const double& b = v[50];
  if (&b == &VectorN::Error) std::cout << "Greska!" << std::endl;

  // Obezbijediti osnovne matematičke operacije za rad sa vektorima, te
  // obezbijediti učitavanje i ispis vektora na standardni izlaz.
  VectorN v1{2.2, 3.1, 4.5};
  VectorN v2{5.6, 21.2, 10};

  std::cout << std::endl;
  std::cout << "v1 " << v1 << std::endl;
  std::cout << "v2 " << v2 << std::endl;

  std::cout << std::endl;
  std::cout << "Zbir: " << v1 + v2 << std::endl;
  std::cout << "Razlika: " << v1 - v2 << std::endl;
  std::cout << "Skalarni prozivod: " << v1 * v2 << std::endl;
  std::cout << "5 * " << v1 << ": " << 5 * v1 << std::endl;

  // Obezbijediti instanciranje vektora korištenjem inicijalizatorske liste ili
  // implicitnog kastovanja iz realnog broja.
  VectorN v3 = 5.0;  // Korištenje inic. liste je već iskorišteno za v1 i v2.

  std::cout << std::endl;
  // Obezbijediti statičku metodu za konstruisanje nula - vektora proizvoljne
  // dimenzionalnosti.
  VectorN v4 = VectorN::ZeroVector(3);
  std::cout << "Nula vektor pomocu staticke f-je: " << v4 << std::endl
            << std::endl;

  // Obezbijediti matematički prikladne operatore poređenja.
  bool eq = v1 == v2;

  // Preklopiti operator funkcijskog poziva za izračunavanje vrijednosti
  // polinoma predstavljenog vektorom.
  std::cout << "Izracunavanje polinoma v1(5): " << v1(5) << std::endl;

  std::cout << std::endl;
  // ComparableVectorN
  // Obezbijediti konstruktor koji prihvata funkciju koja preslikava VectorN u
  // double i VectorN, te implementirati odgovarajuće operatore poređenja
  // upotrebom ove funkcije.
  ComparableVectorN cv(v1, ManhattanDistance);

  // Implementirati kastovanje iz klase VectorN u klasu ComparableVectorN uz
  // korištenje podrazumijevane funkcije za normiranje koja predstavlja
  // Euklidsko rastojanje od koordinatnog početka.
  ComparableVectorN cv1(v1);
  cv1 = v;
  // Implementirati kastovanje iz klase ComparableVectorN u klasu VectorN, uz
  // zanemarivanje funkcije za normiranje
  VectorN v5 = cv;

  // Preklopiti operator dvosmjernog poređenja.
  if (cv < cv1)
    std::cout << "cv < cv1" << std::endl;
  else if (cv > cv1)
    std::cout << "cv > cv1" << std::endl;
  else if (std::is_eq(cv <=> cv1)) //(cv == cv1)
    std::cout << "cv = cv1." << std::endl;
  else
    std::cout << "Neuporedivi." << std::endl;  // kad imaju drugačije norme

  std::cout << std::endl;
  // VectorSetN
  // Obezbijediti umetanje i izbacivanje iz skupa korištenjem operatora dodjele
  // sa dodavanjem i operatora dodjele sa oduzimanjem.Obezbijediti lančano
  // pozivanje operatora.
  VectorSetN vset(3, 3);
  ((vset += v1) += v2) += v4;
  vset -= v4;

  // Obezbijediti funkcije za transformaciju i filtriranje svih vektora iz skupa
  // po nekom pravilu, korištenjem funkcije koja prihvata lambda operator.
  VectorSetN vset1 = vset.map([](const VectorN& vec) { return vec * 2.0; });
  VectorSetN vset2 =
      vset.filter([](const VectorN& vec) { return vec(4) < 100; });

  // Implementirati odgovarajuće funkcije za poređenje skupova (skupovi su
  // identični ukoliko sadrže identične elemente).
  bool c = vset1 == vset2;
  std::cout << "Skupovi \n"
            << vset1 << "i" << std::endl
            << vset2 << (vset1 == vset2 ? "" : "ne") << " sadrze iste elemente"
            << std::endl;

  std::cout << std::endl;
  // Implementirati ispis na standardni izlaz.
  std::cout << vset << std::endl;

  // Implementirati provjeru linearne nezavisnosti vektora iz skupa.
  std::cout << "Vektori " << std::endl
            << vset << (vset.isLinearlyIndependent() ? "su" : "nisu")
            << " linearno nezavisni" << std::endl;
  vset += VectorN::ZeroVector(3);
  std::cout << std::endl;
  std::cout << "Vektori " << std::endl
            << vset << (vset.isLinearlyIndependent() ? "su" : "nisu")
            << " linearno nezavisni" << std::endl;

  // OrderedVectorSetN
  // Obezbijediti umetanje i izbacivanje iz skupa korištenjem operatora dodjele
  // sa dodavanjem i operatora dodjele sa oduzimanjem.Obezbijediti lančano
  // pozivanje operatora.
  ComparableVectorN cv2({1.5, 2.5, 3.5, 4.5});
  ComparableVectorN cv3({3.0, 5.0, 7.0, 9.0});
  OrderedVectorSetN ovset(4, 4);
  OrderedVectorSetN ovset1(4, 4, ManhattanDistance);

  (ovset += cv3) += cv2;
  ovset1 = ovset;
  ovset1 -= cv3;

  // Implementirati odgovarajuće funkcije za poređenje skupova (skupovi su
  // identični ukoliko sadrže identične elemente), te omogućiti poređenje
  // objekata klasa VectorSetN i OrderedVectorSetN, tako da je operator
  // poređenja komutativan.
  bool d = ovset == ovset1;

  bool e = vset == ovset;
  bool f = ovset == vset;

  // Omogućiti ispis na standardni izlaz u sortiranom poretku.
  std::cout << std::endl;
  std::cout << ovset << std::endl;

  // Obezbijediti kastovanje iz skupa uporedivih vektora u skup vektora.
  VectorSetN vsetcast(ovset);

  // Implementirati provjeru linearne nezavisnosti vektora iz skupa.
  std::cout << "Vektori " << std::endl
            << ovset << (ovset.isLinearlyIndependent() ? "su" : "nisu")
            << " linearno nezavisni" << std::endl;

  return 0;
}
