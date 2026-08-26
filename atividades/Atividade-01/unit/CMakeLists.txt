# SPDX-License-Identifier: Apache-2.0
#
# App de teste unitário (ztest) da Atividade-01. Roda separado do app do
# aluno. Quando a atividade tiver lógica isolada em função própria, inclua
# o arquivo-fonte do aluno via $ENV{STUDENT_SRC_DIR} (setado pelo CI), ex:
#
#   target_sources(app PRIVATE $ENV{STUDENT_SRC_DIR}/src/logica.c)
#   target_include_directories(app PRIVATE $ENV{STUDENT_SRC_DIR}/src)

cmake_minimum_required(VERSION 3.28.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(atividade01_unit)

target_sources(app PRIVATE src/test_main.c)
