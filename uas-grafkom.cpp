#include <iostream>
#include <sstream>
#include <string>
#include <glut.h>

// Variabel global untuk posisi kamera
float cameraX = 5.0f, cameraY = 5.0f, cameraZ = 5.0f;
float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;

// Fungsi untuk menggambar teks di layar
void drawText(const std::string& text, float x, float y) {
    glDisable(GL_LIGHTING); // Nonaktifkan pencahayaan agar teks terlihat
    glColor3f(1.0f, 1.0f, 1.0f); // Warna teks (putih)
    glRasterPos2f(x, y); // Atur posisi teks

    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Gambar karakter
    }
    glEnable(GL_LIGHTING); // Aktifkan kembali pencahayaan
}

// Fungsi untuk menginisialisasi pengaturan OpenGL
void initOpenGL() {
    glEnable(GL_DEPTH_TEST);  // Mengaktifkan pengujian kedalaman
    glEnable(GL_LIGHTING);     // Mengaktifkan pencahayaan
    glEnable(GL_LIGHT0);       // Mengaktifkan sumber cahaya pertama
    glEnable(GL_COLOR_MATERIAL); // Mengaktifkan material berwarna

    // Posisi dan properti cahaya
    GLfloat lightPos[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Menyeting posisi dan properti cahaya
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Warna latar belakang biru langit
}

// Fungsi callback untuk keyboard
void handleKeyboard(unsigned char key, int x, int y) {
    const float step = 0.5f; // Kecepatan gerakan kamera
    switch (key) {
    case 'w': // Bergerak maju
        cameraZ -= step;
        break;
    case 's': // Bergerak mundur
        cameraZ += step;
        break;
    case 'a': // Bergerak ke kiri
        cameraX -= step;
        break;
    case 'd': // Bergerak ke kanan
        cameraX += step;
        break;
    case 32: // Tombol spasi
        // Reset koordinat kamera ke posisi awal
        cameraX = 5.0f;
        cameraY = 5.0f;
        cameraZ = 5.0f;
        centerX = 0.0f;
        centerY = 0.0f;
        centerZ = 0.0f;
        break;
    case 27: // ESC untuk keluar
        exit(0);

    }
    glutPostRedisplay(); // Meminta layar di-refresh
}

// Fungsi untuk menggambar meja dengan 4 kaki
void drawTable() {
    // Bagian atas meja
    glDisable(GL_LIGHTING); // Menonaktifkan pencahayaan untuk meja
    glColor3f(0.6f, 0.4f, 0.2f); // Warna coklat kayu
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f); // Memindahkan bagian atas meja
    glScalef(5.0f, 0.2f, 5.0f);  // Menyesuaikan ukuran bagian atas meja
    glutSolidCube(1.0f);  // Menggambar kubus solid untuk bagian atas meja
    glPopMatrix();

    // Kaki meja (4 buah)
    glColor3f(0.5f, 0.3f, 0.1f); // Warna kaki meja lebih gelap
    float legPositions[4][3] = {
        {-2.2f, -1.5f, -2.2f}, // Kaki kiri belakang
        {-2.2f, -1.5f,  2.2f}, // Kaki kiri depan
        { 2.2f, -1.5f, -2.2f}, // Kaki kanan belakang
        { 2.2f, -1.5f,  2.2f}  // Kaki kanan depan
    };

    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glTranslatef(legPositions[i][0], legPositions[i][1], legPositions[i][2]); // Posisi kaki
        glScalef(0.2f, 2.0f, 0.2f); // Ukuran kaki meja
        glutSolidCube(1.0f);  // Menggambar kaki meja
        glPopMatrix();
    }
    glEnable(GL_LIGHTING); // Aktifkan kembali pencahayaan untuk objek lainnya
}

// Fungsi untuk menggambar keranjang piknik (lebih pendek sedikit)
void drawBasket() {
    glColor3f(0.6f, 0.4f, 0.2f); // Warna coklat untuk keranjang

    // Basis keranjang (diperkecil dan diposisikan)
    glPushMatrix();
    glTranslatef(-1.0f, 0.15f, 1.5f);  // Memindahkan keranjang agar tetap berada di atas meja
    glScalef(2.0f, 0.8f, 1.2f);        // Mengurangi tinggi keranjang sedikit
    glutSolidCube(1.0f);  // Menggambar kubus solid untuk keranjang
    glPopMatrix();
}

// Fungsi untuk menggambar teko dan posisinya di ujung meja
void drawTeapot() {
    glColor3f(0.2f, 0.6f, 0.8f); // Warna biru untuk teko
    glPushMatrix();
    glTranslatef(1.5f, 0.0f, 1.5f);  // Memposisikan teko di ujung meja
    glutSolidTeapot(0.5);  // Menggambar teko dengan ukuran 0.5
    glPopMatrix();
}

// Fungsi untuk menggambar buah-buahan (dalam bentuk bola)
void drawFruits() {
    // Apel
    glColor3f(1.0f, 0.0f, 0.0f); // Warna merah untuk apel
    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, -1.5f);  // Memposisikan apel sedikit lebih jauh
    glutSolidSphere(0.2, 20, 20); // Menggambar bola padat untuk apel
    glPopMatrix();

    // Jeruk
    glColor3f(1.0f, 0.5f, 0.0f); // Warna oranye untuk jeruk
    glPushMatrix();
    glTranslatef(1.0f, 0.0f, -1.5f);  // Memposisikan jeruk sedikit lebih jauh
    glutSolidSphere(0.2, 20, 20); // Menggambar bola padat untuk jeruk
    glPopMatrix();

    // Anggur (diwakili oleh sekumpulan bola)
    glColor3f(0.6f, 0.0f, 0.6f); // Warna ungu untuk anggur
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.5f);  // Posisi anggur sedikit lebih jauh

    // Membuat sekumpulan bola kecil untuk anggur
    for (float i = -0.1f; i <= 0.1f; i += 0.1f) {
        for (float j = -0.1f; j <= 0.1f; j += 0.1f) {
            glPushMatrix();
            glTranslatef(i, 0.0f, j);  // Menentukan posisi bola-bola kecil
            glutSolidSphere(0.1, 10, 10); // Menggambar bola kecil untuk anggur
            glPopMatrix();
        }
    }
    glPopMatrix();
}

// Fungsi untuk menggambar piring
void drawPlate() {
    glColor3f(0.9f, 0.9f, 0.9f); // Warna putih untuk piring
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, -0.5f); // Posisi piring di atas meja
    glScalef(1.5f, 0.1f, 1.5f); // Ukuran piring
    glutSolidSphere(0.5, 30, 30); // Menggambar piring berbentuk lingkaran
    glPopMatrix();
}

// Fungsi untuk menggambar gelas
void drawGlass() {
    GLUquadric* quad = gluNewQuadric(); // Membuat objek kuadrik untuk silinder
    glColor3f(0.6f, 0.8f, 1.0f); // Warna biru muda untuk gelas

    // Dinding gelas (silinder)
    glPushMatrix();
    glTranslatef(1.5f, -0.5f, 0.0f); // Posisikan silinder
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotasi agar silinder berdiri
    gluCylinder(quad, 0.2f, 0.2f, 0.5f, 30, 10); // Gambar silinder untuk dinding gelas
    glPopMatrix();

    gluDeleteQuadric(quad); // Hapus objek kuadrik
}

// Fungsi callback untuk menampilkan objek di layar
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,  // Posisi kamera
        centerX, centerY, centerZ,  // Titik yang dilihat
        0.0f, 1.0f, 0.0f);         // Vektor atas kamera

    // Menggambar objek
    drawTable();
    drawBasket();
    drawTeapot();
    drawFruits();
    drawPlate();
    drawGlass();

    // Tampilkan koordinat kamera di layar
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Atur area 2D untuk teks
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::ostringstream oss;
    oss << "Camera Position: (" << cameraX << ", " << cameraY << ", " << cameraZ << ")";
    drawText(oss.str(), 10, 580); // Gambar teks di layar (koordinat kiri atas)

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

// Fungsi callback untuk mengubah ukuran jendela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);  // Mengubah area tampilan
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0); // Menyeting perspektif
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi utama untuk menjalankan program
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); // Ukuran jendela
    glutCreateWindow("3D Table Scene");

    initOpenGL(); // Inisialisasi pengaturan OpenGL

    glutDisplayFunc(display); // Fungsi untuk menampilkan objek
    glutReshapeFunc(reshape); // Fungsi untuk mengubah ukuran jendela
    glutKeyboardFunc(handleKeyboard);// Fungsi untuk menggerakkan kamera

    glutMainLoop();  // Memulai loop utama glut
    return 0;
}