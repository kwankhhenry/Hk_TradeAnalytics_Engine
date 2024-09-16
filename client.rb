

require 'socket'
starttime = Process.clock_gettime(Process::CLOCK_MONOTONIC)

s = TCPSocket.new 'localhost', 5000

s.write("/home/admin/Outside_Project/Hk_TradeAnalytics_Engine/server/test/#{ARGV[0]}.txt\n")

s.each_line do |line|
    #puts line
end

s.close
endtime = Process.clock_gettime(Process::CLOCK_MONOTONIC)
elapsed = endtime - starttime
puts "Elapsed: #{elapsed}"