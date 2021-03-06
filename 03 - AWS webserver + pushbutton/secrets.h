#include <pgmspace.h>

#define SECRET
#define THINGNAME "r0781861-Lander-esp32"

#define AWS_IOT_PUBLISH_TOPIC   "r0781861/measurement"
#define AWS_IOT_PUBLISH_TOPIC2   "r0781861/button"
#define AWS_IOT_SUBSCRIBE_TOPIC "r0781861/led"

const char WIFI_SSID[] = "*******";
const char WIFI_PASSWORD[] = "*******";
const char AWS_IOT_ENDPOINT[] = "a2g39bqtdhth9l-ats.iot.us-west-2.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUCDlVsX9bkqoCxJzbYQzSBlJtTLQwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDIyMjEwNDc1
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMrRb6tRMDtKBXXuCiCh
/0h3tqXuUvjUzRZFM4Xt/vdcgAyihCrAxlRPhS0LCie/hps1jwCawa8AalhhND0d
bLg5DpkCk0WbA84AMmXPgPA6/PoSRyUZywIz4V/TlMzfaChPIJrYBGdNl/ohyATW
SxKEU58B9KUESA+nnFohxVLOFPULgQNlaiz4Pe2u2qeZlOIkiFOCuz6e95Uackl9
QFRBv+yew4ju9ye3Zpv8Puye9IfNG8F63YmoNT9883TKsXXBGwwc2xRFTRLKfGRR
1Oq2kWRUhO6sx5B/z+oI9JZTwWoSsFQE7wvW82fHdMxNBP1PAvd08BC3gUwhM585
/QMCAwEAAaNgMF4wHwYDVR0jBBgwFoAUnfBrxn84QL1/G6Lh7B9CGJZkEHkwHQYD
VR0OBBYEFLpk204TMHFor9kXtmP1k7pyVsfcMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAFH/e7bOmDjcHLBZcwSIefDvj/
gRPDaZTOKW8odOC6mHoYLBkuV+7zNrkfE/ikS1KY0RBuWiQP82XgYP61rv2QLi2i
odrqtiZF8sHJRuUGkYhV/UlhsZ26xZpGcC/+tR/SuMhJwrGuU9VzytmXm3ySEknm
nkrHp9cdYErr5SJ3PZ7ECOAGlELOuSW6hhdUUzhAcvnGb0oSFjwKGpoTjvBHBktH
zZrjMpocVUjui5aXFuDP0YwdN4ERr/2nbwZABznX6cLNXq61wTlWlKE8JbAPpWOs
3N1kho/p0kNnblOpPd+gRFTZgzfNAubcwc4epWsR5NKDPZpF5dk3RMGakhtA
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAytFvq1EwO0oFde4KIKH/SHe2pe5S+NTNFkUzhe3+91yADKKE
KsDGVE+FLQsKJ7+GmzWPAJrBrwBqWGE0PR1suDkOmQKTRZsDzgAyZc+A8Dr8+hJH
JRnLAjPhX9OUzN9oKE8gmtgEZ02X+iHIBNZLEoRTnwH0pQRID6ecWiHFUs4U9QuB
A2VqLPg97a7ap5mU4iSIU4K7Pp73lRpySX1AVEG/7J7DiO73J7dmm/w+7J70h80b
wXrdiag1P3zzdMqxdcEbDBzbFEVNEsp8ZFHU6raRZFSE7qzHkH/P6gj0llPBahKw
VATvC9bzZ8d0zE0E/U8C93TwELeBTCEznzn9AwIDAQABAoIBAGCkQ02ithTKRKfY
8UJzbq0dPg767NZcsAy4lMBwk1lS3kEm/0tP6DEsYwz/gatG++DhOG7VTw0QaZwL
VVT5vGBb77TBIWO9Zaa3OUyB/7J4qSqPow7up2k5R17d9r1Yhs0ORz8BR7fhpVUu
25xScBs2qpHN4MDwtVWgTEQ2a0v0xV2BaIMpWapGeWyq2vh6D6AiiiRzDDICJb1V
tHgftRZ4gtMpl5juD1mkimN95oCBauHVqVIQCl/zq5Xnvse+chmk2EkrL5Lt9iqA
mIp+++//fKOhKoqvoLESRPZJMQgvzpC8bs4TpsbVlluf4PSSEu2TMLM7stUiOlg6
t/LtdiECgYEA7/4PRQ2oE0vTrKY38qVrMu6IjstFl9z7Y/tMfBPL4avcfAAW1V7h
5VlcLGB4BdHBdN2JOQWdJ1qpUt6XXdPSyNgFjICWrW3y9sO8YmSLb6aMqS8xykIC
vRGP8iwKEQ5cPL9IwG40ZIbRpgRjeg6jIQ2BFiwBHsotkgMEaJp62rUCgYEA2Fid
SZipygMUmcdyHyspXWAprdvQRDq6ww3CJGW697Vu7ZZzcjF7JZ1E3RsEpj8qZhgc
YRzqoLSaQJMKNN3Rj44Iy/qf6cmgAp9FsLbiYRPNM5GXev7SJkwFXEdGNwnpO0a3
+KpHVhD4Vw064zF0+Dy/aaSwqSpMB4fmEDG5c9cCgYBrLXb8S8EH/REnRYQu5Rke
wdBSlQ0baSEL4aqiruSaf/oTlqab26femS3E08BGOQrAej9SK+OnM6Hy1F2dFYBJ
GdBAkxy3jya2dWuoNWbgEe03kVAXF6vJbBJxAKHuRA+FQZfn+E+FpX/zOHqEhAzu
Me24TSai7X+0eYx6eqLrEQKBgAbMCe0FAdiZ7izCqmA2T+9iFQ0kSc/K9JEqPn48
P/qGVbzbLDdbPJ466a30qlm6xE8+1K1sZia0ZeA/fmOY0HutH7Og5SNINWG/tUXP
CR+5qonDOjogBWQ0oTp79sXF5vD40NDcMK+QiuzZOo9mv2EJL45XIUG/VXIrH9xE
Y6ozAoGAGcZK+9QLXDuGHMha7vpPmNaYLZQvr+qZ5kdmtAA3EFLoBIBvps3zlGcj
qOAWxZenBfQFBgxdnAc/g+bpYIpIMjox9JRmqzncX9erV1oH5rXXKb1eQHXZM8Rt
fUgDwPuP0alenwVt0MJfpxu2sXZgpxqyWAvvu4eFkgNJQEJOBNA=
-----END RSA PRIVATE KEY-----
)KEY";
