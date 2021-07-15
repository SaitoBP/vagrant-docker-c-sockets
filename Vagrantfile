Vagrant.configure("2") do |config|

  # Manager
  config.vm.define "http-c-server" do |http_c_server|
      http_c_server.vm.box = "bento/ubuntu-18.04"
      http_c_server.vm.network "private_network", ip: "192.168.0.10"

      http_c_server.vm.provision "send server folder", type: "file", source: "./server", destination: "server"
      http_c_server.vm.provision "docker setup", type: "shell", path: "./utils/docker_setup.sh"
  end

  # Node 1
  config.vm.define "node_1" do |node_1|
    node_1.vm.box = "bento/ubuntu-18.04"
    node_1.vm.network "private_network", ip: "192.168.0.20"

    node_1.vm.provision "docker setup", type: "shell", path: "./utils/docker_setup.sh"
  end

  # Node 2
  config.vm.define "node_2" do |node_2|
    node_2.vm.box = "bento/ubuntu-18.04"
    node_2.vm.network "private_network", ip: "192.168.0.30"

    node_2.vm.provision "docker setup", type: "shell", path: "./utils/docker_setup.sh"
  end

end