
let tu="X"
let isover=false;


const change = () =>{
    return tu==="X"?"0":"X"
}

const win=()=>{
let text=document.getElementsByClassName('text');
let wins=[
    [0,1,2],
    [3,4,5],
    [6,7,8],
    [0,3,6],
    
    [1,4,7],
    [2,5,8],
    
    
    [0,4,8],
    [2,4,6],

]
wins.forEach(e=>{
    if((text[e[0]].innerText === text[e[1]].innerText) && (text[e[2]].innerText === text[e[1]].innerText) && (text[e[0]].innerText !== "") ){
        document.querySelector('.info').innerText = text[e[0]].innerText + " Won"
       isover=true;
       document.querySelector('.imgs').getElementsByTagName('img')[0].style.width='50px';
    
          
    }
 
})
}

let box=document.getElementsByClassName("box");
Array.from(box).forEach(element=>{
    let text=element.querySelector('.text');
    element.addEventListener('click',()=>{
        if(text.innerText===''){
            text.innerText=tu;
            tu=change();
      
            win();
            if (isover==false){
                document.getElementsByClassName("info")[0].innerText  = "TURN - " + tu;
            } 
        }

    })
})
btn.addEventListener('click',()=>{
    let text=document.querySelectorAll('.text');
    Array.from(text).forEach(element=>{
        element.innerText=""
    })
    tu="X";isover=false;
    document.getElementsByClassName("info")[0].innerText  = "Turn for " + tu;
    document.querySelector('.imgs').getElementsByTagName('img')[0].style.width = "0px"
    
})
