# 🏨 Hospeda - Sistema de Gerenciamento de Hotel

Projeto desenvolvido em **C** com o objetivo de aplicar conhecimentos de **Algoritmos e Estruturas de Dados I (AEDS I)**, utilizando como contexto o gerenciamento de um hotel.

A aplicação permite controlar clientes, quartos e reservas, além de operações relacionadas à hospedagem, como check-in, check-out e cancelamento.

## 🎯 Objetivo

Desenvolver uma solução organizada para o gerenciamento das principais operações de um hotel, colocando em prática conceitos de algoritmos, estruturas de dados, modularização e manipulação de informações.

## ⚙️ Funcionalidades

### 👤 Clientes
- Cadastro, consulta, listagem e remoção;
- Identificação por ID;
- Armazenamento de nome, CPF e telefone.

### 🚪 Quartos
- Cadastro, consulta, listagem e remoção;
- Consulta de quartos disponíveis;
- Controle de tipo, capacidade, valor da diária e status.

### 📅 Reservas
- Criação, consulta e listagem;
- Consulta das reservas de um cliente;
- Cancelamento de reservas;
- Controle das datas de entrada e saída;
- Cálculo do valor da hospedagem e de multas.

### 🛎️ Hospedagem
- Check-in;
- Check-out;
- Atualização automática do status dos quartos;
- Controle do estado das reservas.

## 🧠 Conceitos aplicados

- Estruturas de dados;
- Structs e enumerações;
- Funções e modularização;
- Algoritmos de busca e manipulação;
- Validação de dados;
- Organização e gerenciamento de informações.

## 🛠️ Tecnologias

- **C**
- **GCC**
- **Git / GitHub**

## 📁 Estrutura

```text
├── include/
├── src/
│   ├── cliente/
│   ├── quarto/
│   ├── reserva/
│   └── main.c
│
└── README.md