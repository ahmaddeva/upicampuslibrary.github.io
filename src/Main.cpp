#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <string>

using namespace std;
int getOption();
int getBook();

int main()
{
    ofstream myFile;
    label_choice:
    int choice = getOption();
    enum option{BUKU = 1, PEMINJAMAN, PENGEMBALIAN, KELUAR};

    while(choice != KELUAR){
        switch (choice)
        {
        case BUKU: {
            int book_choice = getBook();
            while(book_choice != 4){
                // List Buku
                string buku1 = "Your Name";
                string buku2 = "Weathering With You";
                string buku3 = "Re:ZERO";
                
                if (book_choice == 1)
                {
                    myFile.open("data_peminjaman.txt", ios::app);
                    myFile << buku1;
                    myFile << "\t\t\t" << __DATE__ << endl;
                    cout << "Anda telah meminjam buku " << buku1 << "." << endl;
                    cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                    cout << "Press any key to continue...";
                    getch();
                    goto label_choice;
                }
                if (book_choice == 2)
                {
                    myFile.open("data_peminjaman.txt", ios::app);
                    myFile << buku2;
                    myFile << "\t" << __DATE__ << endl;
                    cout << "Anda telah meminjam buku " << buku2 << "." << endl;
                    cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                    cout << "Press any key to continue...";
                    getch();
                    goto label_choice;
                }
                if (book_choice == 3)
                {
                    myFile.open("data_peminjaman.txt", ios::app);
                    myFile << buku3;
                    myFile << "\t\t\t\t" << __DATE__ << endl;
                    cout << "Anda telah meminjam buku " << buku3 << "." << endl;
                    cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                    cout << "Press any key to continue...";
                    getch();
                    goto label_choice;
                }
                
            }
            cout << "Terima kasih dan sampai jumpa!";                  
        }break;
        
        case PEMINJAMAN: {
            ifstream file_("data_peminjaman.txt");
            string judul, tanggal;
            if (file_.is_open())
            {
                while(file_>> judul >> tanggal){
                    cout << judul << endl;
                    cout << tanggal << endl;
                }
            }
            cout << "Press any key to continue...";
            getch();
            goto label_choice;
        }break; 
        
        case PENGEMBALIAN: {

        }break; 
        
        default:
            cout << "Masukkan pilihan yang benar" << endl;
            break;
        }
    }
    cout << "Terima kasih dan sampai jumpa!" << endl;
    cin.get();
    return 0;
}

int getOption(){
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
int getBook(){
    int choice;
    system("cls");
    cout << "\nPilih Buku" << endl;
    cout << "=======================" << endl;
    cout << "1. Your Name" << endl;
    cout << "2. Weathering With You" << endl;
    cout << "3. Re:ZERO" << endl;
    cout << "4. Kembali ke laman utama" << endl;
    cout << "=======================" << endl;
    cout << "Silakan pilih (1-4): ";
    cin >> choice;
    return choice;
}