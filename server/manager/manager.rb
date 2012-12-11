require './config/application.rb'

# def write_registration_denied(socket)
#   packet = ""
#   write_uint8(4, packet)
#   write_bool(false, packet)
#   write_qbytearray("you are not SQUARED", packet)
#   packet_size = ""
#   write_uint16(packet.size, packet_size)
#   packet.prepend(packet_size)
#   socket << packet
# end

server = TCPServer.new('localhost', 33034)

begin
  puts "Server started on #{server.connect_address.ip_unpack.join(":")}"
  loop do
    Thread.start(server.accept) do |socket|
      puts "client #{Addrinfo.new(socket.getpeername).ip_unpack.join(":")} connected"
      p socket.get_packet
      loop do
        # size = read_uint16(socket)
        # p "size: #{size}"
        # type = read_uint8(socket)
        # p "type: #{type}"
        # username = ""
        # username = read_qbytearray(socket)
        # p "username: #{username}"
        # password = read_qbytearray(socket)
        # p "password: #{password}"

        # write_registration_denied(socket)
      end
    end
  end
ensure
  server.close
end
