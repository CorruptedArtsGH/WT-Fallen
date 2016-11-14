using UnityEngine;
using System.Collections;

public class Attack_Trigger : MonoBehaviour {

	[SerializeField] public int attack_Damage = 20; //Inital damage - will require balance

	/*Check if ENEMY is within the collider and tell ENEMY.damage how much damage was taken.*/
	void onTriggerEnter2D(Collider2D col){//OPEN onTrigger
		if(col.isTrigger != true && col.CompareTag("Enemy")){//OPEN IF
			col.SendMessageUpwards("Damage", attack_Damage); 
		}//END IF
	}//END onTrigger

}
