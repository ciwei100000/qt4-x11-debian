Fetched from 4.4.2
treat Https, HTtps, hTTps, ... as https as well

Index: b/src/network/access/qnetworkaccesshttpbackend.cpp
===================================================================
--- a/src/network/access/qnetworkaccesshttpbackend.cpp
+++ b/src/network/access/qnetworkaccesshttpbackend.cpp
@@ -64,7 +64,7 @@
 static QByteArray makeCacheKey(const QUrl &url)
 {
     QUrl copy = url;
-    bool isEncrypted = url.scheme() == QLatin1String("https");
+    bool isEncrypted = url.scheme().toLower() == QLatin1String("https");
     copy.setPort(url.port(isEncrypted ? DefaultHttpsPort : DefaultHttpPort));
     return "http-connection:" + copy.toEncoded(QUrl::RemovePassword | QUrl::RemovePath |
                                                QUrl::RemoveQuery | QUrl::RemoveFragment);
@@ -88,7 +88,8 @@
     }
 
     QUrl url = request.url();
-    if (url.scheme() == QLatin1String("http") || url.scheme() == QLatin1String("https"))
+    QString scheme = url.scheme().lower();
+    if (scheme == QLatin1String("http") || scheme == QLatin1String("https"))
         return new QNetworkAccessHttpBackend;
 
     return 0;
@@ -309,7 +310,7 @@
 void QNetworkAccessHttpBackend::open()
 {
     QUrl url = request().url();
-    bool encrypt = url.scheme() == QLatin1String("https");
+    bool encrypt = url.scheme().toLower() == QLatin1String("https");
     setAttribute(QNetworkRequest::ConnectionEncryptedAttribute, encrypt);
 
     // set the port number in the reply if it wasn't set
