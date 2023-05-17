program main
  implicit none
  integer, parameter :: dp = selected_real_kind(15, 307)
  integer :: n, i, j, n_step, k
  real(dp), allocatable :: A(:,:), x(:), b(:)
  real(dp) :: start_time, end_time, elapsed_time
  integer :: allocation_status

  ! Número de etapas
  n_step = 5

  ! Abre o arquivo para escrita
  open(10, file='tempo_execucao.txt', status='replace')

  do i = 1, n_step
    ! Define o tamanho do sistema
    n = 10000 * i

    ! Aloca a matriz A e os vetores x e b
    allocate(A(n,n), x(n), b(n), stat=allocation_status)

    if (allocation_status /= 0) then
      print *, "Erro: Memória insuficiente para alocar os arranjos!"
      stop
    end if

    ! Inicializa A, x e b com valores aleatórios
    call random_number(A)
    call random_number(x)
    call random_number(b)

    ! Mede o tempo de execução do produto matriz-vetor para o loop externo i
    call cpu_time(start_time)
    do j = 1, n
      b(j) = 0.0_dp
      do k = 1, n
        b(j) = b(j) + A(j,k) * x(k)
      end do
    end do
    call cpu_time(end_time)

    elapsed_time = end_time - start_time

    ! Imprime o tempo de execução para o loop externo i
    print *, "Tempo de execução para n =", n, "(i no loop externo):", elapsed_time, "segundos"

    ! Grava o tempo de execução no arquivo para o loop externo i
    write(10, '(I10, F12.6)') n, elapsed_time

    ! Mede o tempo de execução do produto matriz-vetor para o loop externo j
    call cpu_time(start_time)
    do j = 1, n
      b(j) = 0.0_dp
      do k = 1, n
        b(k) = b(k) + A(k,j) * x(j)
      end do
    end do
    call cpu_time(end_time)

    elapsed_time = end_time - start_time

    ! Imprime o tempo de execução para o loop externo j
    print *, "Tempo de execução para n =", n, "(j no loop externo):", elapsed_time, "segundos"

    ! Grava o tempo de execução no arquivo para o loop externo j
    write(10, '(I10, F12.6)') n, elapsed_time

    ! Libera a memória alocada
    deallocate(A, x, b)
  end do

  ! Fecha o arquivo
  close(10)

end program main
