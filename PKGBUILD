pkgname=ngspice
pkgver=26
pkgrel=2
pkgdesc='Mixed-level/Mixed-signal circuit simulator based on Spice3f5, Ciber1b1, and Xspice.'
url='http://ngspice.sourceforge.net'
license=('BSD')
arch=('i686' 'x86_64')
depends=('libxaw' 'libedit' 'gcc-libs')
source=("http://downloads.sourceforge.net/project/$pkgname/ng-spice-rework/$pkgver/$pkgname-$pkgver.tar.gz"
        "http://downloads.sourceforge.net/project/$pkgname/ng-spice-rework/$pkgver/$pkgname-doc-$pkgver.tar.gz"
        "res.patch"
        "cap.patch"
        "ind.patch")
sha1sums=('7c043c604b61f76ad1941defeeac6331efc48ad2'
          'bc163a47a2b4987c4617c47b132a30ffdc674350'
           'SKIP'
           'SKIP'
   	   'SKIP')
build() {
  
  cd "${srcdir}/${pkgname}-${pkgver}"
  patch -p1 -i $srcdir/res.patch 
  patch -p1 -i $srcdir/cap.patch 
  patch -p1 -i $srcdir/ind.patch 
  ./configure --prefix=/usr \
              --mandir=/usr/share/man \
              --infodir=/usr/share/info \
              --with-readline=yes \
              --with-ngshared
    make
}

package() {
  cd "${srcdir}/${pkgname}-${pkgver}"
  make DESTDIR="$pkgdir" install
  install -D -m644 COPYING "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -D -m644  "$srcdir/$pkgname-doc-$pkgver/manual.pdf" "$pkgdir/usr/share/doc/$pkgname/manual.pdf"
}
