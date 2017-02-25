function graph(file_name)
	f_in = fopen(file_name, "rt");
	coord = str2num(fgetl(f_in));
	width = abs(coord(3) - coord(1));
	height = abs(coord(2) - coord(4));
	
	if coord(1) < coord(3)
		X = coord(1);
	else
		X = coord(3);
	endif

	if coord(2) < coord(4)
		Y = coord(2);
	else
		Y = coord(4);
	endif

	figure
	hold on

	rectangle('Position', [X, Y, width, height],
			  'LineWidth', 3)
	number = print_number = str2num(fgetl(f_in));
	labels = cellstr( num2str([1:number]') );
	tree_X = [];
	tree_Y = [];
	axis("equal");
	while (number ~= 0)
		tree_cord = str2num(fgetl(f_in));
		tree_X = [tree_X, tree_cord(1)];
		tree_Y = [tree_Y, tree_cord(2)];
		number = number - 1;
	endwhile
	printf("Index-ul trebuie sa fie in intervalul [1, %d]\n", print_number);
	printf("Optiuni: quit \- iesire, all \- afisare toti pomii\n");

% 	Pomii sunt numerotati de la 0;

	while (1)
		ind = input('Index sau optiune:', 's');
		if strcmp(ind, 'quit') || strcmp(ind, 'all') 
			break
		endif
		ind = str2num(ind);
		if ind > print_number
			disp('Try another index!');
			continue
		else
			printf('Coordonate: X = %.3f Y = %.3f\n', tree_X(ind), tree_Y(ind));
			plot(tree_X(ind), tree_Y(ind), 'LineWidth', 10, 'r.');
			text(tree_X(ind), tree_Y(ind), num2str(ind), 'VerticalAlignment', 'bottom', ...
														'HorizontalAlignment', 'right');
		endif
	endwhile

if strcmp(ind, 'all')
	plot(tree_X, tree_Y, 'LineWidth', 10, 'r.');
	text(tree_X, tree_Y, labels, 'VerticalAlignment','bottom', ...
    	                         'HorizontalAlignment','right');
endif
H = legend("Limita teren", "Pomi");
T = title("Livada");

set(H, 'FontSize', 15);
set(T, 'FontSize', 30, 'FontWeight', 'bold');
hold off
endfunction
