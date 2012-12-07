require './config/application.rb'

def read_quint8(socket)
  num = ""
  1.times {num << socket.getbyte.to_s(16)}
  num.to_i(16)
end

def read_quint16(socket)
  num = ""
  2.times {num << socket.getbyte.to_s(16)}
  num.to_i(16)
end

def read_quint32(socket)
  num = ""
  4.times {num << socket.getbyte.to_s(16)}
  num.to_i(16)
end

def read_quint64(socket)
  num = ""
  8.times {num << socket.getbyte.to_s(16)}
  num.to_i(16)
end

def read_qbytearray(socket)
  size = read_quint32(socket)
  if size == 0xFFFFFFFF
    nil
  else
    msg = ""
    size.times { msg << read_quint8(socket).chr(Encoding::UTF_8) }
    msg
  end
end
server = TCPServer.new('localhost', 33034)

begin
  loop do
    Thread.start(server.accept) do |socket|
      puts "client #{Addrinfo.new(socket.getpeername).ip_unpack.join(":")} connected"
      loop do
        size = read_quint16(socket)
        p "size: #{size}"
        type = read_quint8(socket)
        p "type: #{type}"
        username = ""
        username = read_qbytearray(socket)
        p "username: #{username}"
        password = read_qbytearray(socket)
        p "password: #{password}"
      end
    end
  end
ensure
  server.close
end
