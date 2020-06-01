# Tugas_UAS

Nama  : Sulthan Zaidan Fauzi
NIM   : 1908107010028

#Login
Format data dalam file login.bin yaitu:
Admin_Zaidan zzz310102
Note : username dan password dipisahkan menggunakan spasi
Pada awal mulai program, user diminta untuk menginput username dan password
Username  : Admin_Zaidan
Password  : zzz310102
Setelah berhasil login, user dapat mengganti username dan password dengan memilih pilihan 6 pada menu

#Procces
Program akan membaca file data.txt dan memprosesnya, kemudian ditampung pada array bertipe struct
Format data dalam file data.txt yaitu:
Nama# Sekolah# Kelas# No_Hp# Program# Biaya# Status;

#Read
Pilihan menu pertama akan menampilkan data yang ada dalam struct yang sebelumnya sudah di proses dari file data.txt

#Search
Pilihan menu kedua akan mencari data berdasarkan nama, user akan diminta untuk menginput nama yang akan dicari

#Add
Pilihan menu ketiga akan menambahkan data, jika nama yang diinput user sudah ada dalam data, maka user diminta untuk menginput nama ulang.
Setelah ditambahkan, data tersebut akan ditambahkan ke dalam file data.txt

#Delete
Pilihan menu keempat akan menghapus data, user akan diminta untuk menginput nama yang akan dihapus datanya.
Setelah dihapus, data yang terbaru akan di tulis ulang ke dalam file data.txt

#Update
Pilihan menu kelima akan mengubah data tertentu, user akan diminta untuk menginput nama untuk diupdate datanya dari nama tersebut.
User juga bisa memilih data apa yang akan diubah. Setelah diubah, data yang terbaru akan ditulis ulang ke dalam file data.txt

#Mengganti username dan password
Pilihan menu keenam, user juga dapat mengganti username dan password. Setelah selesai, user akan diminta untuk melakukan login ulang

#Akhir dari program
Pilihan menu ketujuh akan mengakhir program.
