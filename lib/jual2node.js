// This file maps some functions so that the JualScript engine can run 
// some NodeJS scripts

console = {}
console.log = print;
    
process = {}
process.exit = os.exit;
