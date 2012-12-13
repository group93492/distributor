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

server = TCPServer.new(SERVER_IP, SERVER_PORT)

def confirm_registration(socket)
  socket.send_packet({'type' => 'registration_answer',
                       'registration_result' => true})
end

def reject_registration(socket, denial_reason = "")
  socket.send_packet({'type' => 'registration_answer',
                      'registration_result' => false,
                      'denial_reason' => denial_reason})
end

begin
  puts "Server started on #{server.connect_address.ip_unpack.join(":")}"
  loop do
    Thread.start(server.accept) do |socket|
      puts "client #{Addrinfo.new(socket.getpeername).ip_unpack.join(":")} connected"
      loop do
        current_packet = socket.get_packet
        case current_packet.type
        when 'unknown'
          print "Got unknown-typed packet #{current_packet}\n"
        when 'authorization_request'
        when 'registration_request'
          user = User.register_user(current_packet)
          if user.valid?
            confirm_registration(socket)
          else
            reject_registration(socket, user.errors.messages.to_s)
          end
        end
      end
    end
  end
ensure
  server.close
end
