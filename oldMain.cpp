#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

struct Buku {
    int pk;
    string kode, judul, pengarang, tahun;
};
int getOptionMhs();
int getOptionPtg();
void checkDBBuku(fstream &dataBuku);
int getDBBukuSize(fstream &dataBuku){
    int start, end;
    dataBuku.seekg(0, ios::beg);
    start = dataBuku.tellg();
    dataBuku.seekg(0, ios::end);
    end = dataBuku.tellg();
    return(end-start)/sizeof(Buku);
} 
void writeDataBuku(fstream &data, int posisi, Buku &inputBuku){
    data.seekp((posisi - 1)*sizeof(Buku), ios::beg);
    data.write(reinterpret_cast<char*>(&inputBuku), sizeof(Buku));
}
void addDataBuku(fstream &dataBuku){
    Buku inputBuku;

    inputBuku.pk = 1;
    cout << "Kode: ";
    getline(cin, inputBuku.kode);
    cout << "Judul: ";
    getline(cin, inputBuku.judul);
    cout << "Pengarang: ";
    getline(cin, inputBuku.pengarang);
    cout << "Tahun terbit: ";
    getline(cin, inputBuku.tahun);

    writeDataBuku(dataBuku, 1, inputBuku);
}
int main()
{
    fstream dataBuku;  
    checkDBBuku(dataBuku);

    label_choice:
    int choicePtg = getOptionPtg();
    enum option{TAMBAH = 1, LIHATBUKU, LIHATPEMINJAMAN, KELUAR};
    while(choicePtg != KELUAR){
        switch (choicePtg){
        case TAMBAH: {
            addDataBuku(dataBuku);
            cout << "Data berhasil dibuat" << endl;
            cout << "Buat data baru? y/n";
            int x;
            cin >> x; 
        }break;
        
        case LIHATBUKU: {
            
        }break; 
        
        case LIHATPEMINJAMAN: {

        }break; 
        
        default:
            cout << "Masukkan pilihan yang benar" << endl;
            break;
        }
    }
    // int choiceMhs = getOptionMhs();
    // enum option{BUKU = 1, PEMINJAMAN, PENGEMBALIAN, KELUAR};

    /* while(choiceMhs != KELUAR){
        switch (choiceMhs){
        case BUKU: {
            int sizeBuku = getDBBukuSize(dataBuku);
            cout << sizeBuku;
            int x;
            cin >> x;
        }break;
        
        case PEMINJAMAN: {
            ifstream myFileStream("data_peminjaman.txt");
            if(!myFileStream.is_open()){
                cout << "File failed to open" << endl;
                return 0;
            }
            string judul_buku, tanggal_peminjaman;
            string line;

            cout << "==========Daftar Peminjaman========= \n" << endl;
            while(getline(myFileStream, line)){
                stringstream ss(line);
                getline(ss, judul_buku, ',');
                getline(ss, tanggal_peminjaman, ',');
    
                cout << "Judul: "<< judul_buku << endl;
                cout << "Tanggal Peminjaman: " << tanggal_peminjaman << endl;
                cout << endl;
            }
            myFileStream.close();
            system("pause");
            goto label_choice;
        }break; 
        
        case PENGEMBALIAN: {

        }break; 
        
        default:
            cout << "Masukkan pilihan yang benar" << endl;
            break;
        }
    }
    */
    cout << "Terima kasih dan sampai jumpa!" << endl;
    cin.get();
    return 0;
}

int getOptionMhs(){
    int choice;
    system("cls");
    cout << "\nAplikasi Perpustakaan" << endl;
    cout << "=======================" << endl;
    cout << "1. Pilih buku" << endl;
    cout << "2. Daftar Peminjaman" << endl;
    cout << "3. Pengembalian" << endl;
    cout << "4. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Silakan pilih (1-4): ";
    cin >> choice;
    return choice;
}
int getOptionPtg(){
    int choice;
    system("cls");
    cout << "\nAplikasi Perpustakaan" << endl;
    cout << "=======================" << endl;
    cout << "1. Tambah Buku" << endl;
    cout << "2. Daftar Buku" << endl;
    cout << "3. Daftar Peminjaman" << endl;
    cout << "4. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Silakan pilih (1-4): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return choice;
}
void checkDBBuku(fstream &dataBuku){
    dataBuku.open("data_buku.txt", ios::out |ios::in);
    if (!dataBuku.is_open()){
        dataBuku.open("data_buku.txt",ios::trunc |ios::out | ios::in);
    }
    dataBuku.close();
    
}