import http.server
import socketserver
import socket

PORT = 8080

def get_local_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(('8.8.8.8', 80))
        IP = s.getsockname()[0]
    except Exception:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP

Handler = http.server.SimpleHTTPRequestHandler

print("=" * 60)
print("  SERVIDOR CONTROLE JH021")
print("=" * 60)
print(f"\nServidor rodando em:")
print(f"  - Local: http://localhost:{PORT}")
print(f"  - Rede: http://{get_local_ip()}:{PORT}")
print(f"\nNo iPhone (Safari):")
print(f"  http://{get_local_ip()}:{PORT}/interface.html")
print("\nPressione Ctrl+C para parar\n")
print("=" * 60)

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    httpd.serve_forever()
