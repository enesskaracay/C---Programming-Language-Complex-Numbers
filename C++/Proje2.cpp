/*
 *  Proje2
 *  Karmaşık sayılar ve lineer cebir işlemleri içeren fonksiyonlar sınıflar opratorler..
 * Proje - 2 BP3
 *  29.12.2023
 *  Enes Karaçay // enes.karacay@stu.fsm.edu.tr
 */
#include <iostream>
#include <vector>
using namespace std;
class Imaginary // Imaginary sınıfı, karmaşık sayıların sanal kısmını temsil eder.
{
private:
    double imagi; // Sanal kısım

public:
    Imaginary(double imagiPart)
    { // kurucu fonksiyon Constructor
        imagi = imagiPart;
    }

    Imaginary(const Imaginary &other) // Bir Imaginary nesnesinin kopyasını oluşturur.
    {                                 // copy constructor
        imagi = other.imagi;
    }

    double getimagi() const
    {                 // const çümkü değişmemesi gerekir sabit kalması gerekir "get"
        return imagi; // Sanal kısmı getiririz..
    }

    // Sanal kısmı ayarlıyoru
    void setimagi(double imagiPart)
    { // const değil çünkü değiştiriyoruz.
        imagi = imagiPart;
    }

    void print() const
    {
        std::cout << "Imaginary  Part: " << imagi << "i" << std::endl;
    } // imajinel kısmıı yazdırıyoruz print fonksiyonumuz ile
};

class Complex : public Imaginary // Complex sınıfı, gerçel ve sanal kısımları olan karmaşık sayıları temsil eder.
{
private:
    double re; // Gerçel kısım

public:
    Complex(double real, double imagi)    :    Imaginary(imagi),  re(real) {} 
              // Yeni bir Complex nesnesi oluşturur.
    Complex(const Complex &other) :    Imaginary(other.getimagi())   ,  re(other.re) {} // copy Constructor
    // Bir Complex nesnesinin kopyasını oluşturur.
    double getRe() const // Gerçel kısmı getiren fonksiyon returnnnnn
    {
        return re;
    }

    void setRe(double real) // Gerçel kısmı ayarlayan fonksiyon
    {                       // const değil çünkü değiştiriyoruz
        re = real;
    }

    void print() const // Complex sayıyı ekrana yazdıran fonksiyon
    {
        std::cout << "Complex number : " << re << " "; // ekrana complex number yazıp öncelkle real kısmı yazdırıyoruz

        if (getimagi() < 0)
        {
            std::cout << " - " << -getimagi(); // Sanal kısım negatifse, "-" işareti ile negatif sanal kısmı yazdır
                                               // Sanal kısım pozitifse, "+" işareti ile pozitif sanal kısmı yazdır
        }
        else
        {
            std::cout << " + " << getimagi();
        }
        std::cout << "i" << std::endl; // "i" eklendikten sonra yeni satıra geç
    }
    Complex operator+(const Complex &other) const
    { // +  operatörü aşırı yükleme
        double resultReal = re + other.re;
        double resultImagi = getimagi() + other.getimagi();

        return Complex(resultReal, resultImagi);
    }

    Complex operator-(const Complex &other) const
    { // -  operatörü aşırı yükleme
        double resultReal = re - other.re;
        double resultImagi = getimagi() - other.getimagi();

        return Complex(resultReal, resultImagi);
    }

    Complex operator*(const Complex &other) const
    { // * operatörü aşırı yükleme
        double realPa = re * other.re;
        double imagiPa = getimagi() * other.getimagi();
        double realPa2 = re * other.getimagi();
        double imagiPa2 = getimagi() * other.re;

        double reResult = realPa - imagiPa;
        double İmagiResult = realPa2 + imagiPa2;
        return Complex(reResult, İmagiResult);
    }

    Complex operator/(const Complex &other) const
    {                                                                   // / operatörü aşırı yükleme
        double realPa = re * other.re;                                  // paydanın gerçel kısmı
        double reKare = other.re * other.re;                            // paydanın sanal kısmı
        double imagiKare = other.getimagi() * other.getimagi();         // paydanın sanal kısmı
        double payda = reKare + imagiKare;                              // paydanın toplamı
        double rePay = re * other.re + getimagi() * other.getimagi();   // payın gerçel kısmı
        double imagPay = getimagi() * other.re - re * other.getimagi(); // payın sanal kısmı
        double reResult = rePay / payda;                                // sonucun gerçel kısmı
        double imagResult = imagPay / payda;                            // sonucun sanal kısmı
        return Complex(reResult, imagResult);                           // Yeni bir Complex nesnesi oluşturularak sonuç döndürülüyor
    }

    Complex &operator=(const Complex &other)
    { // =  operatörü aşırı yükleme
        if (this != &other)
        {
            re = other.re;              // real kısmı atıyoruz
            setimagi(other.getimagi()); // Sanal kısmı atıyoruz
        }
        return *this; // Elde edilen sonucu döndürüyoruz
    }

    Complex &operator+=(const Complex &other)
    {                                                        // +=  operatörü aşırı yükleme
        re = re + other.re;                                  // real ksımını topluyoruz
        double imaginewpart = getimagi() + other.getimagi(); // imajinel olan kısmı topluyoruz
        setimagi(imaginewpart);                              // oluşturduğumuz imaginewpartı setimagiye atarak Karmaşık sayımızın ekranda çıkacak yeni imajinel kısmını oluşturuyourz
        return *this;                                        // Elde edilen sonucu döndürüyoruz
    }

    Complex &operator-=(const Complex &other)
    {                                                        // -=  operatörü aşırı yükleme
        re = re - other.re;                                  // real ksımını çıkarıyoruz
        double imaginewpart = getimagi() - other.getimagi(); // imajinel olan kısmı çıkarıyoruz
        setimagi(imaginewpart);                              // oluşturduğumuz imaginewpartı setimagiye atarak Karmaşık sayımızın ekranda çıkacak yeni imajinel kısmını oluşturuyourz
        return *this;                                        // Elde edilen sonucu döndürüyoruz
    }

    Complex &operator*=(const Complex &other)
    {                                                   // *=  operatörü aşırı yükleme
        double realPa = re * other.re;                  // real olan kısımları çarpıyoruz
        double imagiPa = getimagi() * other.getimagi(); // Çarpma işlemini adım adım yapıyorum ve burda imajinel kısmı çarpıyorum
        double realPa2 = re * other.getimagi();         // real olan kısımla imajinel olan kısmı çarpıyoruz
        double imagiPa2 = getimagi() * other.re;        // real olan kısımla imajinel olan kısmı çarpıyoruz

        double reResult = realPa - imagiPa;      // real olan kısmı çarptık çıkan sonuçtan imajinel olan kısmı da çarpmıştık onu çıkarıyoruz
        double İmagiResult = realPa2 + imagiPa2; // kalan kısımları topluyoruz
        re = reResult;                           // Sonuçları gerçek ve sanal kısma atıyorum
        setimagi(İmagiResult);                   // sanal olan kısmı setimagiye atıyoruz dönsün diye
        return *this;                            // Elde edilen sonucu döndür
    }

    Complex &operator/=(const Complex &other)
    { // /=  operatörü aşırı yükleme
        double reKare = other.re * other.re;
        double imagiKare = other.getimagi() * other.getimagi(); // burda çoğu yaptığımız işlem yukarda yine var burda tekrarlıyoruz
        double imagpayda = reKare + imagiKare;
        double realpay = re * other.re + getimagi() * other.getimagi(); // eşlenik ile çaprma yapıp daha sonasında bölme yapıyoruz kural gereği
        double imagpay = getimagi() * other.re - re * other.getimagi();
        re = realpay / imagpayda;
        double degisken = imagpay / imagpayda;
        setimagi(degisken);
        return *this; // Elde edilen sonucu döndür
    }
    
    bool operator==(const Complex &other) const // ==  operatörü aşırı yükleme
    {
        bool reEqual = (re == other.re);
        bool imagiEqual = (getimagi() == other.getimagi());
        bool resultPart = (reEqual) ? imagiEqual : false; // Her iki kısmın da eşit olup olmadığını kontrol ediyorum
        return resultPart;                                // Sonucu döndürüyoruz
    }
};

class Vector
{
private:
    std::vector<Complex> elements; // Vektörün karmaşık sayı elemanlarını tutan vektör
    size_t size;                   // Vektörün boyutu

public:
    Vector(size_t siz, const std::vector<Complex> &elm) // Kurucu fonksiyon, vektör boyutu ve elemanları alır ve atar aşşağda
    {
        size = siz;
        elements = elm;
    }

    Vector(const Vector &other)
    { // Vektörün boyutunu ve elemanlarını kopyala
        size = other.size;
        elements = other.elements;
    }

    size_t getSize() const
    { // Vektörün boyutunu döndüren fonksiyon
        return size;
    }

    std::vector<Complex> getElements() const // Vektörün elemanlarını içeren vektörü döndüren fonksiyon
    {
        return elements;
    }

    void print() const
    { // Vector sınıfının print() metodu
        std::cout << "[";
        for (size_t i = 0; i < size; ++i)
        {
            std::cout << elements[i].getRe() << " "; // Reel kısmı yazdır
            if (elements[i].getimagi() < 0)
            {
                std::cout << "- " << -elements[i].getimagi(); // Negatif imagineler için düzgün biçimde yazdır
            }
            else
            {
                std::cout << "+ " << elements[i].getimagi(); // Pozitif imagineler için düzgün biçimde yazdır
            }
            std::cout << "i";
            if (i != size - 1)
            {
                std::cout << "   "; // Elemanlar arası boşluk bırak
            }
        }
        std::cout << "]"; // parantez kapat
    }
};

class Matrix
{
private:
    std::vector<std::vector<Complex>> elements; // Matrisin karmaşık sayı elemanlarını tutan 2D vektör
    size_t row;                                 // Matrisin satır sayısı
    size_t col;                                 // Matrisin kolon yani sütun sayısı

public:
    Matrix(size_t ro, size_t co, const std::vector<std::vector<Complex>> &elm) // Kurucu fonksiyon, matris boyutları ve elemanları alır
    {
        row = ro;
        col = co;
        elements = elm;
    }

    Matrix(const Matrix &other)
    {
        row = other.row;
        col = other.col;
        elements = other.elements;
    }

    size_t getRow() const // Matrisin satır sayısını döndüren fonksiyon
    {
        return row;
    }

    size_t getCol() const // Matrisin sütun sayısını döndüren fonksiyon
    {
        return col;
    }

    std::vector<std::vector<Complex>> getElements() const // Matrisin elemanlarını içeren 2D vektörü döndüren fonksiyon
    {
        return elements;
    }

    void setElement(size_t ro, size_t co, const Complex &value) // Belirli bir konumdaki matris elemanını ayarlayan fonksiyon
    {
        if (ro < row && co < col)
        {
            elements[ro][co] = value; // istenilen satır sütüna istenilen elemanı  yazdırır
        }
        else
        {
            throw std::invalid_argument("Invalid matrix element indices"); // geçersiz bir sütün veya satır verirdr uyarı mesajı yazdırcaz throw ile atcaz
        }
    }

    void print() const
    {
        std::cout << "Matrix : " << std::endl;
        for (size_t i = 0; i < row; ++i) // Matrisin her bir satırını döngü içinde işliyoruz
        {
            for (size_t j = 0; j < col; ++j) // Matrisin her bir sütununu döngü içinde işliyoruz
            {
                double rePart = elements[i][j].getRe(); // Karmaşık sayının gerçel ve sanal kısımlarını alıyoruz
                double imagiPart = elements[i][j].getimagi();
                std::cout << rePart << "   "; // Karmaşık sayıları düzgün formatta yazdırma
                if (imagiPart < 0)
                {
                    std::cout << "- " << -imagiPart; // Sanal kısım negatifse "-" işareti ekliuoruz
                }
                else
                {
                    std::cout << "+ " << imagiPart; // Sanal kısım pozitifse "+" işareti ekliyoruz
                }
                std::cout << "i\t\t\t"; // Her karmaşık sayı arasına boşluk ekleyerek matrisi düzenliyoruz
            }

            std::cout << std::endl;
        }
    }

    Matrix transpose() const
    {
        Matrix newResult(col, row, elements); // yeni bir matrix oluşturuyoruz
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j) // elemanların yerleri değiştircez yani satır ve sütünlar değişecek
            {
                newResult.elements[j][i] = elements[i][j];
            }
        }
        return newResult; // oluşturduğumuz bu matrisi return yapıyoruz
    }

    double determinant() const // Matrisin determinantını hesaplayan fonksiyon
    {
        if (row != col)
        { // Matris boyutunu kontrol et, determinant sadece kare matrisler için tanımlıdır
            throw std::invalid_argument("Determinant is only defined for square matrices.");
        }
        if (row == 1) // 1x1 matrisin determinantı, direkt olarak elemanın kendisidir
        {
            return elements[0][0].getRe();
        }
        if (row == 2 && col == 2) // 2x2 matrisin determinantı ad-bc formülü ile hesaplanır
        {
            double deter = elements[0][0].getRe() * elements[1][1].getRe() - elements[0][1].getRe() * elements[1][0].getRe();
            return deter;
        }
        else if (row == 3)
        { // 3x3 matrisin determinantı Sarrus kuralı ile hesaplanır
            double deter = 0.0;
            deter += elements[0][0].getRe() * (elements[1][1].getRe() * elements[2][2].getRe() - elements[1][2].getRe() * elements[2][0].getRe());
            deter -= elements[0][1].getRe() * (elements[1][0].getRe() * elements[2][2].getRe() - elements[1][2].getRe() * elements[2][0].getRe());
            deter += elements[0][2].getRe() * (elements[1][0].getRe() * elements[2][1].getRe() - elements[1][1].getRe() * elements[2][0].getRe());
            return deter;
        }
        else // Diğer durumlar için determinant hesaplaması yapmıyorum 3x3 den faazla olan mattrislerin determinantı hesaplanamaz diye yazdırıyorum eğer 3x3 den fazla matris gelirse hesaplanmaycak ve ekrana bu mesaj yazacak
        {
            throw std::invalid_argument("Determinant calculation for matrices larger than 3 x 3 is not implemeneted.");
        }
    }
};

class SquareMatrix : public Matrix
{
public:
    SquareMatrix(size_t size, const std::vector<std::vector<Complex>> &elm) : Matrix(size, size, elm) // Parametre olarak matris boyutu ve elemanları alarak SquareMatrix oluşturur
    {
        if (size != elm.size() || size != elm[0].size()) // Verilen boyut ve elemanlar, bir kare matrisi oluşturacak şekilde uygun mu diye kontrol edilir
        {
            throw std::invalid_argument("Invalid matrix dimesions for SquareMatrix."); // değilse ekrana uyarı mesajı gelir bilgi
        }
    }
    void print() const // print ile ekrana yazdırıyoruz matrisi kare matrisse
    {
        std::cout << "\nSquareMatrix: " << std::endl;
        Matrix::print();
    }
};

class IdentityMatrix : public Matrix // Birim matris sınıfı, Matrix sınıfından türetiyoruz
{
public:
    IdentityMatrix(size_t size, const std::vector<std::vector<Complex>> &elm) : Matrix(size, size, elm) // Parametre olarak matris boyutu ve elemanları alarak IdentityMatrix oluşturur
    {
        if (size != elm.size() || size != elm[0].size()) // Verilen boyut ve elemanlar, bir kare matrisi oluşturacak şekilde uygun mu diye kontrol edilir
        {
            throw std::invalid_argument("Invalid matrix dimesions for SquareMatrix."); // değilse ekrana uyarı mesajı gelir bilgi
        }
        // Matrisi birim matris yapacak şekilde elemanlar atanır
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            { // Köşegen elemanlar 1, diğer elemanlar 0 olarak atanır
                if (i == j)
                {
                    setElement(i, j, Complex(1, 0)); // Köşegen elemanlar 1, diğer elemanlar 0
                }
                else
                {
                    setElement(i, j, Complex(0, 0)); // Köşegen elemanlar 1, diğer elemanlar 0
                }
            }
        }
    }

    void print() const // Birim matrisi ekrana yazdıran print fonksiyonu
    {
        std::cout << "\nIdentityMatrix: " << std::endl;
        Matrix::print(); // Matrix sınıfının print fonksiyonu kullanılarak matris içeriği yazdırılır
    }
};
int main()
{
    // Kurucu fonksiyonu çağırarak Imaginary sınıfından nesne oluştur
    Imaginary imagiNumber17(5.5);
    // Kopyalama kurucusunu çağırarak başka bir nesne oluştur
    Imaginary imagiNumber18 = imagiNumber17;

    // imajinel olan kısmı print fonksiyonumuz ile ekrana yazdırıuoruz
    imagiNumber17.print();
    imagiNumber18.print();

    Complex complexNum(17.0, 18.0);
    complexNum.print();

    Complex otherComplexNum = complexNum;
    complexNum.print();

    otherComplexNum.setRe(27.0);
    otherComplexNum.setimagi(28.0);
    otherComplexNum.print();

    std::cout << "****************************************************************" << std::endl;
    // Complex sınıfından nesneler oluşturalım operatörleri denemek için
    Complex comNum1(6.0, -7.0);
    Complex comNum2(4.0, 1.0);

    Complex sumComplex = comNum1 + comNum2; // +  operatörü testi
    std::cout << "SUM  = ";
    sumComplex.print();

    Complex differenceComplex = comNum1 - comNum2; // -  operatörü testi
    std::cout << "Difference  = ";
    differenceComplex.print();

    Complex productComplex = comNum1 * comNum2; // *  operatörü testi
    std::cout << "Product  = ";
    productComplex.print();

    Complex divideComplex = comNum1 / comNum2; // /  operatörü testi
    std::cout << "Divide  = ";
    divideComplex.print();

    std::cout << "-------------------------------------------------------------" << std::endl;

    Complex comple1cpy = comNum1;
    comNum1 = comple1cpy;
    comNum1 += comNum2;
    std::cout << " += operator result : "; // += operatörü testi
    comNum1.print();

    comNum1 = comple1cpy;
    comNum1 -= comNum2;
    std::cout << " -= operator result : "; // -= operatörü testi
    comNum1.print();

    comNum1 = comple1cpy;
    comNum1 *= comNum2;
    std::cout << " *= operator result : "; // *= operatörü testi
    comNum1.print();

    comNum1 = comple1cpy;
    comNum1 /= comNum2;
    std::cout << " /= operator result : "; // /= operatörü testi
    comNum1.print();

    std::cout << "Eşitlik ve Atama Kontrolleri Yapiliyor" << std::endl;

    comNum1 = comNum2;
    bool esitMi = (comNum1 == comNum2);

    // Eşitlik operatörü ile kontrol edelim

    std::cout << "Is Equal : " << (esitMi ? "Equal" : "Not Equal") << std::endl;
    // Yeni bir kompleks sayı oluşturuyorum

    Complex newComplexNum(9.0, -3.5);

    // Atama operatörü ile ikinci kompleks sayıyı yeni oluşturulan kompleks sayıya atayalım
    comNum2 = newComplexNum;

    // Eşitlik operatörü ile kontrol edelim
    esitMi = (comNum1 == newComplexNum);

    std::cout << "Is Equal : " << (esitMi ? "Equal " : "Not Equal ") << std::endl;
    std::cout << "****************************************************************" << std::endl;

    std::vector<Complex> elm1 = {Complex(12, 13), Complex(45, 65), Complex(-2, -66)};
    std::vector<Complex> elm2 = {Complex(9, 2), Complex(-5, 52), Complex(2, -17)};

    Vector vec1(elm1.size(), elm1);
    Vector vec2(elm2.size(), elm2);

    std::cout << "Vector Vec1 : " << std::endl;
    vec1.print();

    std::cout << std::endl;

    std::cout << "\nVector Vec2 : " << std::endl;
    vec2.print();

    std::cout << "\nCopy Constructor Vector Calisiyor";
    Vector cpyVector(vec2);
    std::cout << "\nCopy Vector : \n";
    cpyVector.print();

    std::cout << std::endl;

    std::vector<std::vector<Complex>> elm3 = {{Complex(5, -2), Complex(1, 6)}, {Complex(-8, 9), Complex(3, 4)}};
    std::vector<std::vector<Complex>> elm4 = {{Complex(20, 21), Complex(22, 23), Complex(24, 25)}, {Complex(26, 27), Complex(28, 29), Complex(30, 31)}, {Complex(32, 33), Complex(34, 35), Complex(36, 37)}};

    Matrix mat1(elm3.size(), elm3[0].size(), elm3);
    Matrix mat2(elm4.size(), elm4[0].size(), elm4);

    std::cout << std::endl;

    std::cout << "\nMatrix Mat1 : " << std::endl;
    mat1.print();

    std::cout << std::endl;

    std::cout << "Matrix Mat2 : " << std::endl;
    mat2.print();

    std::cout << std::endl;

    std::cout << "Copy Constructor Calisiyor";
    Matrix cpyMatrix(mat2);
    std::cout << "\nCopy Matrix : \n";
    cpyMatrix.print();

    std::cout << std::endl;
    std::cout << "****************************************************************" << std::endl;

    try
    {

        SquareMatrix squareMat(2, elm3);
        squareMat.print(); // Oluşturulan SquareMatrix'i yazdıralım

        std::cout << std::endl;
        std::cout << "****************************************************************" << std::endl;

        IdentityMatrix identityMat(2, elm3);
        identityMat.print();

        std::cout << std::endl;

        std::cout << "Copy Construtor Calisiyor" << std::endl;
        IdentityMatrix cpyIdentityMat(identityMat);
        cpyIdentityMat.print();

        std::cout << std::endl;
        std::cout << "****************************************************************" << std::endl;

        Matrix matrix(3, 3, elm4);
        std::cout << "\nOriginal Matrix : " << std::endl;
        matrix.print();

        Matrix transposedMatrix = matrix.transpose(); // Transpozunu hesaplayıp ekrana yazdıralım
        std::cout << "\nTransposed Matrix : " << std::endl;
        transposedMatrix.print();

        // Determinantını hesaplayıp ekrana yazdıralım
        double deter = matrix.determinant();
        std::cout << "\n Determinant of the Matrix : " << deter << std::endl;
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument(std::string("Error : ") + e.what()); // Hata mesajını oluşturup fırlat
    }
    return 0;
}
