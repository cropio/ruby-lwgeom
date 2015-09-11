task :test do
  test_files_ = ::Dir.glob("test/*_test.rb") 
  test_files_.each do |path_|
    load path_
    puts "Loaded testcase #{path_}"
  end
end

