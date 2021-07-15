# Prova Recuperação

## Objetivos

- ✔ Server HTTP em C/C++ com rotas e retorno 404 e 200

- ✔ Socket em C/C++ em container

- ✔ Provisão do ambiente com Vagrant

- ✔ Autenticação via Keycloack

- ✔ Cluster de Docker Swarm e nodes funcionando com replicas da aplicação distribuida (Pelo menos **uma** replica para cada serviço)

## Instruções

1 - Quando as tres VMs estiverem inicializadas, entre na `http-c-server`, ela sera nossa Manager

2 - Use o seguinte comando para iniciar o swarm

```shell
sudo docker swarm init --advertise-addr 192.168.0.10
```

3 - Em seguida, use o comando retornado pela ação anterior para poder cadastrar os nodes um e dois como workers

4 - Confira se o Manager e os Workers estão vinculados

```shell
sudo docker node ls
```
