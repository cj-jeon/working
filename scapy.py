from scapy.all import *

# IPアドレスとポート番号を設定
src_ip = "192.168.2.107"
dst_ip = "192.168.2.107"
src_port = 12345
dst_port = 80

# SYNパケットを作成
syn = IP(src=src_ip, dst=dst_ip) / TCP(sport=src_port, dport=dst_port, flags='S')

# SYNパケットを送信し、応答を受け取る
syn_ack = sr1(syn)

# ACKパケットを作成
ack = IP(src=src_ip, dst=dst_ip) / TCP(sport=src_port, dport=dst_port, flags='A', seq=syn_ack.ack, ack=syn_ack.seq + 1)

# ACKパケットを送信
send(ack)
