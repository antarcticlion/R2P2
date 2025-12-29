require "fileutils"

unless ENV.include? "PICO_SDK_PATH"
  ENV["PICO_SDK_PATH"] = "#{File.dirname(__FILE__)}/lib/pico-sdk"
end
unless ENV.include? "PICO_EXTRAS_PATH"
  ENV["PICO_EXTRAS_PATH"] = "#{File.dirname(__FILE__)}/lib/pico-extras"
end

PICO_SDK_TAG = "2.2.0"
PICO_EXTRAS_TAG = "sdk-#{PICO_SDK_TAG}"

def mruby_config(vm, board)
  "#{File.expand_path('..', __FILE__)}/build_config/r2p2-#{vm}-#{board}.rb"
end

def mruby_build_path(vm, board)
  "#{File.expand_path('..', __FILE__)}/lib/picoruby/build/r2p2-#{vm}-#{board}"
end

def def_board(board)
  case board
    # --------------------------------------------------------------
    # If you want to add more board settings, enter the definition name here.
    # when '((board definition name))'
    # PICO_BOARD=((pico-sdk board definition file name))
    #  (Maybe, pico-sdk/src/boards/include/boards/*.h)
    #
    # Compiler definition values​written here will be inherited by CMake.
    # If you want to write the value 0, be careful to use 0L or 0U, otherwise the compiler definition itself will disappear.
    # Compiler definition values​to be inherited by rake are written in build_config/*.rb.
  when 'weact2350b'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=weact_studio_rp2350b_core ' +
    '-D FLASH_XIP_QSPI_SIZE_MB=16 ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=12 ' +
    '-D PICO_DEFAULT_UART_RX_PIN=13 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=8 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=9 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  when 'weact2350b_psram'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=weact_studio_rp2350b_core ' +
    '-D FLASH_XIP_QSPI_SIZE_MB=16 -D RP2350_WITH_PSRAM=1 -D RP2350_PSRAM_CS=0u ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=12 ' +
    '-D PICO_DEFAULT_UART_RX_PIN=13 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=8 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=9 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  when 'pimoroniPicoPlus2'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=pimoroni_pico_plus2_rp2350 ' +
    '-D FLASH_XIP_QSPI_SIZE_MB=16 ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=34 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=35 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=32 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=33 ' +
    ' '
  when 'pimoroniPicoPlus2_psram'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=pimoroni_pico_plus2_rp2350 ' +
    '-D FLASH_XIP_QSPI_SIZE_MB=16 -D RP2350_WITH_PSRAM=1 -D RP2350_PSRAM_CS=47 ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=34 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=35 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=32 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=33 ' +
    ' '
  when 'pico2_4MB'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=pico2 ' +
    '-D FLASH_XIP_QSPI_SIZE_MB=4 ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  when 'pico2_compat_8MB'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=pico2 ' +
    '-D FLASH_XIP_QSPI_SIZE_MB=8 ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  when 'pico2_compat_16MB'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=pico2 ' +
    '-D FLASH_XIP_QSPI_SIZE_MB=16 ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
    # --------------------------------------------------------------
  when 'pico2_w'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=pico2_w -D USE_WIFI=1 ' +
    '-D CYW43_DEFAULT_PIN_WL_DATA_OUT=24u ' +
    '-D PICO_FLASH_SIZE_BYTES=4194304u ' +
    '-D CYW43_WL_GPIO_LED_PIN=0u ' +
    '-D CYW43_DEFAULT_PIN_WL_DATA_OUT=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_DATA_IN=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_HOST_WAKE=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_CLOCK=29u ' +
    '-D CYW43_DEFAULT_PIN_WL_REG_ON=23u ' +
    '-D CYW43_DEFAULT_PIN_WL_CS=25u ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  when 'pico2_w_4MB'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=pico2_w -D USE_WIFI=1 ' +
    '-D FLASH_XIP_QSPI_SIZE_MB=4 ' +
    '-D PICO_FLASH_SIZE_BYTES=4194304u ' +
    '-D CYW43_WL_GPIO_LED_PIN=0u ' +
    '-D CYW43_DEFAULT_PIN_WL_DATA_OUT=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_DATA_IN=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_HOST_WAKE=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_CLOCK=29u ' +
    '-D CYW43_DEFAULT_PIN_WL_REG_ON=23u ' +
    '-D CYW43_DEFAULT_PIN_WL_CS=25u ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  when 'pico2'
    '-D PICO_PLATFORM=rp2350 -D PICO_BOARD=pico2 ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  when 'pico_w'
    '-D PICO_PLATFORM=rp2040 -D PICO_BOARD=pico_w -D USE_WIFI=1 ' +
    '-D PICO_FLASH_SIZE_BYTES=2097152u ' +
    '-D CYW43_WL_GPIO_LED_PIN=0u ' +
    '-D CYW43_DEFAULT_PIN_WL_DATA_OUT=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_DATA_IN=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_HOST_WAKE=24u ' +
    '-D CYW43_DEFAULT_PIN_WL_CLOCK=29u ' +
    '-D CYW43_DEFAULT_PIN_WL_REG_ON=23u ' +
    '-D CYW43_DEFAULT_PIN_WL_CS=25u ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  else
    '-D PICO_PLATFORM=rp2040 -D PICO_BOARD=pico ' +
    '-D PICO_DEFAULT_LED_PIN=25 ' +
    '-D PICO_DEFAULT_UART_TX_PIN=0u ' +
    '-D PICO_DEFAULT_UART_RX_PIN=1 ' +
    '-D PICO_DEFAULT_I2C_SDA_PIN=4 ' +
    '-D PICO_DEFAULT_I2C_SCL_PIN=5 ' +
    '-D PICO_DEFAULT_SPI_SCK_PIN=18 ' +
    '-D PICO_DEFAULT_SPI_TX_PIN=19 ' +
    '-D PICO_DEFAULT_SPI_RX_PIN=16 ' +
    '-D PICO_DEFAULT_SPI_CSN_PIN=17 ' +
    ' '
  end
end

def def_build_type(mode)
  case mode
  when 'debug'
    "-D CMAKE_BUILD_TYPE=Debug -D PICORUBY_DEBUG=1"
  else
    "-D CMAKE_BUILD_TYPE=Release -D NDEBUG=1"
  end
end

def def_r2p2_name(vm, board)
  "-D R2P2_NAME=R2P2-#{vm.upcase}-#{board.upcase}"
end

def def_msc(mode)
  '-D PICORUBY_MSC_FLASH=1'
end

def def_picorb_vm(vm)
  vm == 'picoruby' ? '-D PICORB_VM_MRUBYC=1' : '-D PICORB_VM_MRUBY=1'
end

def build_dir(vm, board, mode)
  "build/#{vm}/#{board}/#{mode}"
end

task :setup do
  sh "git submodule update --init"
  FileUtils.cd "lib/picoruby" do
    sh "bundle install"
  end
end

%w[picoruby microruby].each do |vm|
  namespace vm do
    # --------------------------------------------------------------
    # If you want to add more board settings, enter the definition name here.
    # Prepare a file name .rb based on vm, board, and mode in build_config/
    %w[pico pico_w pico2 pico2_w weact2350b pimoroniPicoPlus2 pico2_4MB pico2_w_4MB pico2_compat_8MB pico2_compat_16MB weact2350b_psram pimoroniPicoPlus2_psram].each do |board|
    # --------------------------------------------------------------
      namespace board do
        %w[debug prod].each do |mode|
          desc "Build #{vm} for #{board} (#{mode})"
          task mode => :check_pico_sdk do
            dir = build_dir(vm, board, mode)
            FileUtils.mkdir_p dir
            FileUtils.cd "lib/picoruby" do
              sh "rake test" if ENV['DO_TEST']
              sh "MRUBY_CONFIG=#{mruby_config(vm, board)} #{mode=='debug' ? 'PICORUBY_DEBUG=1' : ''} rake"
            end
            defs = <<~DEFS
              -D EXTRA_LIBRARY_PATH=#{mruby_build_path(vm, board)}/lib \
              -D EXTRA_INCLUDE_DIR=#{mruby_build_path(vm, board)}/include \
              -D PICO_CYW43_SUPPORTED=1 \
              -D MRUBY_CONFIG=#{mruby_config(vm, board)} \
              -D BUILD_DIR=#{dir} \
              #{def_picorb_vm(vm)} \
              #{def_r2p2_name(vm, board)} \
              #{def_board(board)} \
              #{def_build_type(mode)} \
              #{def_msc(mode)}
            DEFS
            sh "cmake -B #{dir} #{defs}"
            sh "cmake --build #{dir}"
          end
        end

        desc "Clean #{vm} for #{board} (both debug and prod)"
        task :clean do
          FileUtils.cd "lib/picoruby" do
            config = mruby_config(vm, board)
            if File.exist?(config)
              sh "MRUBY_CONFIG=#{config} rake clean"
            end
          end
          %w[debug prod].each do |mode|
            dir = build_dir(vm, board, mode)
            FileUtils.rm_f(Dir["#{dir}/R2P2*.*"]) if Dir.exist? dir
          end
        end
      end
    end
  end
end

task :check_pico_sdk => :check_pico_sdk_path do
  FileUtils.cd ENV['PICO_SDK_PATH'] do
    if `git describe --tags --exact-match`.chomp != PICO_SDK_TAG
      raise <<~MSG
        pico-sdk #{PICO_SDK_TAG} is not checked out!\n
        Tips for dealing with:\n
        cd #{ENV['PICO_SDK_PATH']} && \\
          git fetch origin --tags && \\
          git checkout #{PICO_SDK_TAG} && \\
          git submodule update --recursive\n
      MSG
    end
  end
  FileUtils.cd ENV['PICO_EXTRAS_PATH'] do
    if `git describe --tags --exact-match`.chomp != PICO_EXTRAS_TAG
      raise <<~MSG
        pico-extras #{PICO_EXTRAS_TAG} is not checked out!\n
        Tips for dealing with:\n
        cd #{ENV['PICO_EXTRAS_PATH']} && \\
          git fetch origin --tags && \\
          git checkout #{PICO_EXTRAS_TAG} && \\
          git submodule update --recursive\n
      MSG
    end
  end
end

task :check_pico_sdk_path do
  %w(PICO_SDK_PATH PICO_EXTRAS_PATH).each do |env|
    unless ENV[env]
      raise <<~MSG
        Environment variable `#{env}` does not exist!
      MSG
    end
  end
end
