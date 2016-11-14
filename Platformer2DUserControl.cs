using System;
using UnityEngine;
using UnityStandardAssets.CrossPlatformInput;

namespace UnityStandardAssets._2D
{
    [RequireComponent(typeof (PlatformerCharacter2D))]
	public class Platformer2DUserControl : MonoBehaviour
    {
        private PlatformerCharacter2D character;
        private bool isJumping;
		private bool isCrouched;
		private bool isAttacking;

        private void Awake()
        {
            character = GetComponent<PlatformerCharacter2D>();
        }


        private void Update()
        {
            if (!isJumping)
            {
                isJumping = CrossPlatformInputManager.GetButtonDown("Jump");
            }
			isCrouched = CrossPlatformInputManager.GetButton("Crouch");
			isAttacking = CrossPlatformInputManager.GetButton ("Attack");
        }


        private void FixedUpdate()
        {
            // Read the inputs.
            float h = CrossPlatformInputManager.GetAxis("Horizontal");

            // Pass all parameters to the character control script.
            character.Move(h, isCrouched, isJumping);
			character.Attack (isAttacking);
            isJumping = false;

        }
    }
}
