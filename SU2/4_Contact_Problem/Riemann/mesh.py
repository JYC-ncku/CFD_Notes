NX= 1000
NY= 1000
L= 1.0
H= 1.0

N_nodes= (NX + 1) * (NY + 1)
N_elems= NX * NY

with open("4_Contact_Problem.su2", "w") as f:
	# Define dimension
	f.write("NDIME = 2\n")

	# Write node number (9 means square)
	f.write(f"NELEM = {N_elems}\n")
	elem_id = 0
	for j in range(NY):
		for i in range(NX):
			N1 = j * (NX + 1) + i
			N2 = N1 + 1
			N3 = N2 + (NX + 1)
			N4 = N1 + (NX + 1)
			f.write(f"9 {N1} {N2} {N3} {N4} {elem_id}\n")
			elem_id += 1

	# Wrtie coordinate
	f.write(f"NPOIN = {N_nodes}\n")
	Node_id= 0
	for j in range(NY + 1):
		y = j * (H / NY)
		for i in range(NX + 1):
			x = i * (L / NX)
			f.write(f"{x:.6f} {y:.6f} {Node_id}\n")
			Node_id += 1

	# Write Boundary
	f.write("NMARK = 4\n")

	# Write a function to store boundary
	def write_marker(tag, elems):
	        f.write(f"MARKER_TAG= {tag}\n")
        	f.write(f"MARKER_ELEMS= {len(elems)}\n")
	        for n1, n2 in elems:
        		    f.write(f"3 {n1} {n2}\n")

	# Collect points for the four edges (Note: The order of the SU2 boundary points must be counter-clockwise so that the normal vector points outward).
	bottom = [(i, i+1) for i in range(NX)]
	top    = [((NY) * (NX + 1) + i + 1, (NY) * (NX + 1) + i) for i in range(NX)]
	right  = [(j * (NX + 1) + NX, (j + 1) * (NX + 1) + NX) for j in range(NY)]
	left   = [((j+1) * (NX + 1), j * (NX + 1)) for j in range(NY)]

	write_marker("Bottom", bottom)
	write_marker("Top", top)
	write_marker("Right", right)
	write_marker("Left", left)

	print(f"Create {N_elems} cells successfully!\n")
