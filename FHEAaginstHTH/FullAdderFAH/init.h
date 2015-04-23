
    cerr << "Setting up FHEW \n";
    FHEW::Setup();
    cerr << "Generating secret key ... ";
    LWE::SecretKey LWEsk;
    LWE::KeyGen(LWEsk);
    cerr << " Done.\n";
    cerr << "Generating evaluation key ... this may take a while ... ";
    FHEW::EvalKey EK;
    FHEW::KeyGen(&EK, LWEsk);
    cerr << " Done.\n\n";
    cerr << "Testing homomorphic NAND " << count << " times.\n"; 
    cerr << "Circuit shape : (a NAND b) NAND (c NAND d)\n\n";
